//
// Created by dcavalei on 24-09-2022.
//

#include <fstream>
#include <iostream>
#include <utility>
#include "serverConf.h"
#include "http/http.h"

namespace app {
  std::unique_ptr<ServerConf> ServerConf::Builder::parse(std::string_view path) {
      YAML::Node const config = YAML::LoadFile(path.data());
      std::unique_ptr<ServerConf> ptr = std::make_unique<ServerConf>();

      for (auto const &s: config["server"]) {
          ptr->_serverSet.insert(parserServer(s.first.as<std::string>(), s.second));
      }

      return ptr;
  }

  Server ServerConf::Builder::parserServer(std::string name, YAML::Node const &node) {
      Server s;

      s.name = std::move(name);
      std::cout << "server name: " << s.name << std::endl;
      setListen(node, s);
      setLocation(node, s);
      return s;
  }

  void ServerConf::Builder::setLocation(YAML::Node const &node, Server &s) {
      if (node["location"]) {
          for (auto &l: node["location"]) {
              auto path = l.first.as<std::string>();
              auto &locationNode = l.second;
              s.locations.insert(
                      Location{
                              .path = path,
                              .root = locationNode["root"].as<std::string>(path),
                              .allowedMethods = setAllowedMethods(path, locationNode),
                              .redirect = setRedirect(path, locationNode),
                              .autoindex = locationNode["autoindex"].as<bool>(false),
                              .cgi = locationNode["cgi"].as<bool>(false)
                      });
          }
      }
      s.locations.insert(
              Location{
                      .path = "/",
                      .root = "/",
                      .allowedMethods = {http::HTTP_METHODS.begin(), http::HTTP_METHODS.end()},
                      .redirect = std::nullopt,
                      .autoindex = false,
                      .cgi = false
              }
      );
  }

  void ServerConf::Builder::setListen(YAML::Node const &node, Server &s) {
      using vector = std::vector<int>;

      if (node["listen"]) {
          try {
              for (int n: node["listen"].as<vector>(vector{80})) {
                  s.ports.insert(n);
              }
          } catch (std::exception &e) {
              throw std::runtime_error('\n' + s.name +
                                       ":\n\tlisten: [<port>, ...]");
          }
      }
  }

  std::set<std::string> ServerConf::Builder::setAllowedMethods(const std::string &path, YAML::Node const &node) {
      using vector = std::vector<std::string>;

      if (node["allowed-methods"]) {
          std::set<std::string> set;
          for (auto const &m: node["allowed-methods"].as<vector>()) {
              if (m == "GET" || m == "POST" || m == "DELETE") {
                  set.insert(m);
              } else {
                  throw std::runtime_error('\n' + path +
                                           ":\n\tallowed-methods: [GET, POST, DELETE]");
              }
          }
          return set;
      } else {
          return {http::HTTP_METHODS.begin(), http::HTTP_METHODS.end()};
      }
  }

  std::optional<Redirect> ServerConf::Builder::setRedirect(std::string const &path, YAML::Node const &node) {
      if (node["redirect"]) {
          try {
              return Redirect{
                      .code = validateStatusCode(node["redirect"]["code"].as<int>()),
                      .url = validateUrl(node["redirect"]["url"].as<std::string>())
              };
          } catch (std::exception &e) {
              throw std::runtime_error(std::string(e.what()) + '\n'
                                       + path +
                                       ":\n\tredirect:"
                                       "\n\t\tcode: <status_code>"
                                       "\n\t\turl: <url>");
          }
      } else {
          return std::nullopt;
      }
  }

  http::status_code ServerConf::Builder::validateStatusCode(int code) {
      if (code == 301 || code == 302 || code == 303 || code == 304 ||
          code == 305 || code == 306 || code == 307 || code == 308) {
          return static_cast<http::status_code>(code);
      } else {
          throw std::runtime_error("redirect code must be between 301 and 308");
      }
  }

  std::string const &ServerConf::Builder::validateUrl(std::string const &url) {
      if (url.find("http://") == 0 || url.find("https://") == 0) {
          return url;
      } else {
          throw std::runtime_error("redirect url must start with http:// or https://");
      }
  }
  std::set<Server> const &ServerConf::getServers() const {
      return _serverSet;
  }
  ServerConf::const_iterator ServerConf::find(std::string const &name) const {
      return _serverSet.find(Server{name, {}, {}});
  }
  ServerConf::const_iterator ServerConf::begin() const {
      return _serverSet.begin();
  }
  ServerConf::const_iterator ServerConf::end() const {
      return _serverSet.end();
  }
} // app