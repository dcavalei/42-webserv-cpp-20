//
// Created by dcavalei on 18-09-2022.
//

#include <unistd.h>
#include <csignal>
#include <sys/stat.h>
#include <sys/syslog.h>
#include <iostream>
#include "serverApp.h"

namespace app {
  ServerApp &ServerApp::instance() {
      static ServerApp sa = ServerApp();
      return sa;
  }

  void ServerApp::start(int argc, char *argv[]) {
      _cliOptions = ConfigFactory<CliOptions>::make_unique(argc, argv);
      _signalHandler = std::make_unique<SignalHandler>();

      if (_cliOptions->as<bool>(option::DAEMON)) {
          daemonize(_signalHandler);
      }

      _signalHandler->bind(SIGINT, [](int i) {
          std::cout << "signal " << i << std::endl;
          on = false;
      });

      _serverConf = ServerConf::Builder::parse("../conf/config.yaml");



      while (on);
  }

  void ServerApp::daemonize(std::unique_ptr<SignalHandler> const &sigHandler) {
      pid_t pid;

      if ((pid = fork()) < 0) { throw std::runtime_error("fork failed"); }
      if (pid > 0) { exit(EXIT_SUCCESS); }
      if (setsid() < 0) { exit(EXIT_FAILURE); }

      sigHandler->bind(SIGCHLD, SignalHandler::IGNORED);
      sigHandler->bind(SIGHUP, SignalHandler::IGNORED);

      if ((pid = fork()) < 0) { exit(EXIT_FAILURE); }
      if (pid > 0) { exit(EXIT_SUCCESS); }
      umask(0);
      chdir("/");
      for (auto x = sysconf(_SC_OPEN_MAX); x >= 0; x--) {
          close(static_cast<int>(x));
      }
      openlog("webserv-neo", LOG_PID, LOG_DAEMON);
  }
  ServerApp::~ServerApp() {
      if (_cliOptions->as<bool>(option::DAEMON)) {
          syslog(LOG_NOTICE, "webserv exited");
          closelog();
      }
  }
} // app