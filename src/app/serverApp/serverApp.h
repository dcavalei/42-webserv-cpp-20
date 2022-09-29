//
// Created by dcavalei on 18-09-2022.
//

#ifndef SRC_SERVERAPP_SERVERAPP_H
#define SRC_SERVERAPP_SERVERAPP_H

#include <memory>
//#include "log/log.h"
#include "../configFactory/configFactory.h"
#include "../signalHandler/signalHandler.h"

namespace app {

  class ServerApp {
    public:
      ServerApp(const ServerApp &) = delete;
      ServerApp &operator=(const ServerApp &) = delete;
      ServerApp(ServerApp &&) = delete;
      ServerApp &operator=(ServerApp &&) = delete;
      ~ServerApp();

      static ServerApp &instance();
      static void daemonize(const std::unique_ptr<SignalHandler>& sh);
      void start(int argc, char *argv[]);

    private:
      ServerApp() = default;

    public:
      static inline volatile std::sig_atomic_t on = 42;
    private:
      std::unique_ptr<CliOptions> _cliOptions;
      std::unique_ptr<SignalHandler> _signalHandler;
      std::unique_ptr<ServerConf> _serverConf;
  };
} // app

#endif //SRC_SERVERAPP_SERVERAPP_H
