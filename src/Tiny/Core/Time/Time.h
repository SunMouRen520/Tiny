#pragma once

#include "Tiny/Types.h"
#include "Tiny/Def.h"
#include <chrono>

namespace Tiny{
    /*
    TODO: high resolution time
    */

    class Time{
    public:
        Time();
        ~Time() = default;
        void Init();
        /*
            @brief  Get number of seconds since unix epoch.
        */
        double GetTime() const;

        /*
            @brief  Get Number of seconds since start.
        */
        double GetTimeSinceLaunch() const;

        /*
            @brief  Get the logic number of seconds since start.
        */
        double GetLogicTimeSinceLaunch() const;

        /*
            @brief update by logic loop
        */
        void Update();

    private:
        std::chrono::seconds _startTime;
        double _logicTime;
    };
}
