//
// Created by dcavalei on 24-09-2022.
//

#ifndef SRC_APP_CONFIGFACTORY_SERVERCONF_SERVERCONF_H
#define SRC_APP_CONFIGFACTORY_SERVERCONF_SERVERCONF_H

#include <string>
#include <memory>
#include "yaml-cpp/yaml.h"
#include "./server/server.h"

namespace app {

  class ServerConf {
    public:
      using const_iterator = std::set<Server>::const_iterator;

      class Builder;

      [[nodiscard]] std::set<Server> const &getServers() const;
      [[nodiscard]] const_iterator find(std::string const &name) const;
//      [[nodiscard]] const_iterator find(int name) const; see later
      [[nodiscard]] const_iterator begin() const;
      [[nodiscard]] const_iterator end() const;

    private:
      std::set<Server> _serverSet;
  };

  class ServerConf::Builder {
    public:
      [[nodiscard]] static std::unique_ptr<ServerConf> parse(std::string_view path);

    private:
      static Server parserServer(std::string name, YAML::Node const &node);
      static void setListen(YAML::Node const &node, Server &s);
      static void setLocation(YAML::Node const &node, Server &s);
      static std::set<std::string> setAllowedMethods(const std::string &path, YAML::Node const &node);
      static std::optional<Redirect> setRedirect(std::string const &path, YAML::Node const &node);
      static http::status_code validateStatusCode(int code);
      static std::string const &validateUrl(std::string const &url);
  };
} // app

#endif //SRC_APP_CONFIGFACTORY_SERVERCONF_SERVERCONF_H
