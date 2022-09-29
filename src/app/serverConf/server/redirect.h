//
// Created by dcavalei on 29-09-2022.
//

#ifndef SRC_APP_SERVERCONF_SERVER_REDIRECT_H
#define SRC_APP_SERVERCONF_SERVER_REDIRECT_H

#include "http/http.h"

namespace app {

  struct Redirect {
      http::status_code code;
      std::string url;
  };
} // app

#endif //SRC_APP_SERVERCONF_SERVER_REDIRECT_H
