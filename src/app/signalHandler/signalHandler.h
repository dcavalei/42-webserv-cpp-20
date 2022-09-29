//
// Created by dcavalei on 24-09-2022.
//

#ifndef SRC_APP_SIGNALHANDLER_SIGNALHANDLER_H
#define SRC_APP_SIGNALHANDLER_SIGNALHANDLER_H

#include <csignal>

namespace app {

  /**
   * @brief Wrapper around signal
   */
  class SignalHandler {
    public:
      static void bind(int sig, void(*func)(int));

      [[maybe_unused]] static constexpr sighandler_t DEFAULT = SIG_DFL;
      [[maybe_unused]] static constexpr sighandler_t IGNORED = SIG_DFL;
  };
} // app

#endif //SRC_APP_SIGNALHANDLER_SIGNALHANDLER_H
