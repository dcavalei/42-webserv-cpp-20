//
// Created by dcavalei on 18-09-2022.
//

#ifndef SRC_CONFIGFACTORY_CONFIGFACTORY_H
#define SRC_CONFIGFACTORY_CONFIGFACTORY_H

#include <utility>
#include "cliOptions/cliOptions.h"

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
      static T make(Args... values) { return T(values...); }

      template<typename... Args>
      static std::unique_ptr<T> make_unique(Args... values) { return std::make_unique<T>(values...); }

      template<typename... Args>
      static std::shared_ptr<T> make_shared(Args... values) { return std::make_shared<T>(values...); }

  };
} // app

#endif //SRC_CONFIGFACTORY_CONFIGFACTORY_H
