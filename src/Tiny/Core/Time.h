#pragma once

#include "Tiny/Types.h"
#include "Tiny/Macro.h"

namespace Tiny{
  class Time{
  public:
    /*
      @brief  Get number of seconds since unix epoch.
    */
    static double GetTime();

    /*
      @brief  Get Number of seconds since start.
    */
    static double GetTimeSinceStartUp();

    /*
      @brief  Get the logic number of seconds since start.
    */
    static double GetLogicTime();
  };

  class TimeModule{
  public:
    DEF_INSTANCE(TimeModule)

    void Init();

    /*
      @brief Increate logic time by one logical frame delta.
    */
    void Update();

  }
}
