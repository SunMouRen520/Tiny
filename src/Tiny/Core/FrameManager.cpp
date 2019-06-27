#include "Tiny/Core/FrameManager.h"
#include "Tiny/Core/Service.h"

#include <assert.h>

namespace Tiny{
    FrameManager::FrameManager()
    :_frameCount(0)
    ,_currentFrameBeginTime(0.0)
    , _frameDropDelta(100)
    ,_logicalFrameCount(0){
        SetLogicalFps(60);
        SetTargetFps(60);
		_lastFrameDelta = 1 / _targetFps;
    }

    void FrameManager::OnFrameBegin(double currentFrameBeginTime, double lastFrameDelta){
        if(lastFrameDelta > _frameDropDelta){
            Service::Log().W("FrameDrop detected! delta:{}", lastFrameDelta);
        }

        _currentFrameBeginTime = currentFrameBeginTime;
        _lastFrameDelta = lastFrameDelta;
        _frameCount++;

        _realFps = (UnsignedByte)((1.0 / lastFrameDelta) * 0.9 + _realFps * 0.1);
    }

    void FrameManager::SetLogicalFps(UnsignedByte logicalFps){
        assert(logicalFps > 0);
        _logicalFps = logicalFps;
        _logicalDelta = 1.0 / logicalFps;
    }

    void FrameManager::SetTargetFps(UnsignedByte fps){
        assert(fps > 0);
        _targetFps = fps;
        _targetDelta = 1.0 / fps;
    }

    void FrameManager::OnLogicalFrameBegin(){
        _logicalFrameCount++;
    }
}
