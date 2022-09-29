//
// Created by dcavalei on 24-09-2022.
//

#include "signalHandler.h"

namespace app {
  void SignalHandler::bind(int sig, void (*func)(int)) {
      std::signal(sig, func);
  }
} // app