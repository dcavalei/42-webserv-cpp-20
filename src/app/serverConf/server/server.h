//
// Created by dcavalei on 27-09-2022.
//

#ifndef SRC_APP_SERVERCONF_SERVER_SERVER_H
#define SRC_APP_SERVERCONF_SERVER_SERVER_H

#include <cstdint>
#include <string>
#include <set>
#include "location.h"

namespace app {

  struct Server {
      bool operator<(Server const &other) const { return name < other.name; };

      std::string name;
      std::set<int> ports;
      std::set<Location> locations;
  };
} // app

#endif //SRC_APP_SERVERCONF_SERVER_SERVER_H
