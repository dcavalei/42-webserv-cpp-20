//
// Created by dcavalei on 18-09-2022.
//

#include <cstring>
#include "cliOptions.h"

namespace app {

  CliOptions::CliOptions(int argc, char *argv[])
          : _map({{Option::DAEMON, false}}) {
      for (int i = 1; i < argc; ++i) {
          if (std::strlen(argv[0]) >= _bufferSize) {
              continue;
          }
          char name[_bufferSize];
          char value[_bufferSize];
          if (std::sscanf(argv[i], "-%[^=]=%s", name, value) != 2) {
              continue;
          }
          addOption(name, value);
      }
  }

  void CliOptions::addOption(std::string const &name, std::string const &value) {
      if (name == "daemon") {
          _map[Option::DAEMON] = (value == "on");
      } else {
      }
  }

  bool CliOptions::contains(Option o) const {
      return _map.contains(o);
  }
} // app