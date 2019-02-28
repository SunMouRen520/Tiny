#pragma once

#include "Tiny/Types.h"

#include <unordered_map>

namespace Tiny{
    enum class TimePrecision{
        SEC,
        MILISEC,
        MACROSEC,
    };

    /*
        @brief  Abstract timeline,  can be used in animation clip, audio clip etc.
    */
    class Timeline{
    public:
        using ID = std::size_t;
        /*
            @brief
            @param  endTime = 0 stand for endless.
        */
        static ID CreateTimeline(TimePrecision prec, float startTime , float timeStep, float endTime, bool loop);

        static void DeleteTimeline(ID);

        static float GetTime(ID);

        //called by TimeSystem
        void Update();

    private:
        struct TimelineObj{
            TimePrecision prec;
            float startTime;
            float timeStep;
            float endTime;
            bool loop;

            float currentTime;
            TimelineObj(TimePrecision p, float s, float t, float e, bool r)
            :prec(p)
            ,startTime(s)
            ,timeStep(t)
            ,endTime(e)
            ,loop(r){
                currentTime = startTime;
            }
        };
        static std::unordered_map<ID, TimelineObj> _timelines;
        static ID _uniqueID;
    };
}
