//
// Created by dcavalei on 18-09-2022.
//

#ifndef SRC_SERVERAPP_SERVERAPP_H
#define SRC_SERVERAPP_SERVERAPP_H

#include <memory>
//#include "log/log.h"
#include "../configFactory/configFactory.h"

namespace app {

  class ServerApp {
    private:
      ServerApp() = default;
    public:
      ServerApp(const ServerApp &) = delete;
      ServerApp &operator=(const ServerApp &) = delete;
      ServerApp(ServerApp &&) = delete;
      ServerApp &operator=(ServerApp &&) = delete;
      ~ServerApp();

      static ServerApp &instance();
      static void daemonize();
      void start(int argc, char *argv[]);

    private:
      std::unique_ptr<CliOptions> _cliOptions;
  };
} // app

#endif //SRC_SERVERAPP_SERVERAPP_H
