#pragma once

#include "Tiny/Types.h"
#include "Tiny/Def.h"
#include <chrono>

namespace Tiny{
    /*
    TODO:
    1.是否应该直接使用std::chrono类型作为返回值，而不是使用Long
    */
    enum class TimePrecision{
        SEC,
		MILLISEC, //毫秒
        MICROSEC, //微秒
    };

    class Time{
    public:
        Time();
        ~Time() = default;
        void Init();
        /*
            @brief  Get time since unix epoch.
            @return integer represtation in TimePrecision unit
        */
        Long GetTime(TimePrecision p = TimePrecision::SEC) const;

        /*
            @brief  Get time since start.
            @return integer represtation in TimePrecision unit
        */
        Long GetTimeSinceLaunch(TimePrecision p = TimePrecision::SEC) const;


        /*
            @brief  Get the logic number of seconds since start.
        */
        double GetLogicTimeSinceLaunch() const;

        /*
            @brief update by logic loop
        */
        void Update();

    private:
        std::chrono::milliseconds _startTimeMilliSec;
        std::chrono::seconds _startTimeSec;
        std::chrono::microseconds _startTimeMacroSec;
        double _logicTime;
    };
}
