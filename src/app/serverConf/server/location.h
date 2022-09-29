//
// Created by dcavalei on 28-09-2022.
//

#ifndef SRC_APP_SERVERCONF_SERVER_LOCATION_H
#define SRC_APP_SERVERCONF_SERVER_LOCATION_H

#include "http/http.h"
#include "redirect.h"

namespace app {

  struct Location {
      bool operator<(Location const &other) const { return path < other.path; };

      std::string path;
      std::string root;
      std::set<std::string> allowedMethods;
      std::optional<Redirect> redirect;
      bool autoindex;
      bool cgi;
  };
} // app

#endif //SRC_APP_SERVERCONF_SERVER_LOCATION_H
