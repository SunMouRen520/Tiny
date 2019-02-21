#ifndef TINY_CORE_TIME_H
#define TINY_CORE_TIME_H

#include "Tiny/Types.h"

namespace Tiny{
  class Time{
  public:
    /*
      @brief  Get frame count since start up.
    */
    static Int GetFrameCount();

    /*
      @brief  Get number of seconds since unix epoch.
    */
    static float GetTime();

    /*
      @brief  Get Number of seconds since game start.
    */
    static float GetTimeSinceStartUp();
  }
}

#endif
