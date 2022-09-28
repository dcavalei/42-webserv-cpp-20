//
// Created by dcavalei on 18-09-2022.
//

#ifndef SRC_APP_CONFIGFACTORY_CLIOPTIONS_CLIOPTIONS_H
#define SRC_APP_CONFIGFACTORY_CLIOPTIONS_CLIOPTIONS_H

#include <map>
#include <any>
#include <type_traits>
#include <stdexcept>

namespace app {
  enum class Option {
      DAEMON
  };

  class CliOptions {
    public:
      CliOptions(int argc, char *argv[]);
      CliOptions() = delete;

      [[nodiscard]] bool contains(Option o) const;
      template<typename T>
      [[nodiscard]] T &at(Option o) {
          return std::any_cast<T &>(_map.at(o));
      }
    private:
      void addOption(std::string const &name, std::string const &value);

      static constexpr size_t _bufferSize = 128;
      std::map<Option, std::any> _map;
  };
} // app

#endif //SRC_APP_CONFIGFACTORY_CLIOPTIONS_CLIOPTIONS_H
