#pragma once

#include "Tiny/Types.h"
// #include "IronBranch/Notion/Signals.h"

namespace Tiny{
    class Engine;
    /*
    Frame:
    1. logical fps 和 fps target在游戏初始化时就设置好 且在游戏运行过程中不变
    */
    class FrameManager{
        friend class Engine;
    public:
		FrameManager();
        ~FrameManager() = default;
        /*
        @brief  set logical fps as target fps, which may not be the real fps due to many circumstance, such as render tick may cost too much time and so on.
        */
        void SetLogicalFps(UnsignedByte fps);

        /*
        @brief  set total
        */
        void SetTargetFps(UnsignedByte fps);

        /*
        @brief  get real fps. calclated by passed frame delta time by weights.
        */
        UnsignedByte GetFps() const{ return _realFps; }

        /*
        @brief  get total fps target. default is 60.
        */
        UnsignedByte GetTargetFps() const{ return _targetFps; }

        /*
        @brief  get target frame delta
        */
        Double GetTargetFrameDelta() const{ return _targetDelta;}
        /*
        @brief  get logical fps
        */
        UnsignedByte GetLogicalFps() const {return _logicalFps;}

        /*
        @brief  get logical frame delta
        */
        Double GetLogicalFrameDelta() const { return _logicalDelta;}

        /*
        @brief  get last frame's running time(real time).
        @return default value is 1 / _targetFps;
        */
        double GetLastFrameDeltaTime() const { return _lastFrameDelta; }

        /*
        @brief  get current frame begin time(real time).(constant through whole frame)
        */
        double GetFrameBeginTime() const { return _currentFrameBeginTime;}


        /*
        @brief  Get frame count since start up.
        */
        UnsignedLong GetFrameCount() const { return _frameCount;}

        UnsignedLong GetLogicalFrameCount() const { return _logicalFrameCount;}

        /*
        @brief set upward frame delta threshold.

        If last frame delta cost more time than this,
        TODO:
            we should expose some
        */
        // void SetFrameDeltaThreshold(int millisec);


    protected:
        void OnFrameBegin(double currentFrameBeginTime, double lastFrameDelta);
        void OnLogicalFrameBegin();

    private:
        UnsignedLong _frameCount;
        UnsignedLong _logicalFrameCount;

        UnsignedByte  _targetFps;
        Double        _targetDelta;
        UnsignedByte  _logicalFps;
        Double        _logicalDelta;

        UnsignedByte _realFps;

        double _currentFrameBeginTime;
        double _lastFrameDelta;

        int _frameDropDelta;
        // IronBranch::Signals<>
    };
}
