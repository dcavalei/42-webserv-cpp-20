//
// Created by dcavalei on 18-09-2022.
//

#ifndef SRC_CONFIGFACTORY_CONFIGFACTORY_H
#define SRC_CONFIGFACTORY_CONFIGFACTORY_H

#include <utility>
#include "./cliOptions/cliOptions.h"
#include "../serverConf/serverConf.h"

namespace app {

  /**
   * @brief Useless factory class
   *
   * This class was implemented to study templates.
   * ConfigFactory<T>::make(Args...) == T(Args...)
   * @tparam T
   */
  template<class T>
  class ConfigFactory {
    public:
      template<typename... Args>
      static std::unique_ptr<T> make_unique(Args... values) {
          auto ptr = std::make_unique<T>(values...);
          verify(std::move(ptr));
          return ptr;
      }

    private:
      static std::unique_ptr<CliOptions> &&verify(std::unique_ptr<CliOptions> &&ptr) {
          return std::move(ptr);
      }

//      static std::unique_ptr<CliOptions> &&verify(std::unique_ptr<CliOptions> &&ptr) {
//          return std::move(ptr);
//      }

  };
} // app

#endif //SRC_CONFIGFACTORY_CONFIGFACTORY_H
