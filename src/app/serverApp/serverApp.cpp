//
// Created by dcavalei on 18-09-2022.
//

#include <unistd.h>
#include <csignal>
#include <sys/stat.h>
#include <sys/syslog.h>
#include "serverApp.h"

namespace app {
  ServerApp &ServerApp::instance() {
      static ServerApp sa = ServerApp();
      return sa;
  }

  void ServerApp::start(int argc, char *argv[]) {
      _cliOptions = ConfigFactory<CliOptions>::make_unique(argc, argv);
      if (_cliOptions->at<bool>(Option::DAEMON)) {
          daemonize();
      }

      while (42);
  }

  void ServerApp::daemonize() {
      pid_t pid;

      if ((pid = fork()) < 0) { throw std::runtime_error("fork failed"); }
      if (pid > 0) { exit(EXIT_SUCCESS); }
      if (setsid() < 0) { exit(EXIT_FAILURE); }

      /* Catch, ignore and handle signals */
      //TODO: Implement a working signal handler */
      signal(SIGCHLD, SIG_IGN);
      signal(SIGHUP, SIG_IGN);

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
      if (_cliOptions->at<bool>(Option::DAEMON)) {
          syslog(LOG_NOTICE, "webserv exited");
          closelog();
      }
  }
} // app