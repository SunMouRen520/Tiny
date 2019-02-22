#include "Tiny/Core/FrameManager.h"


namespace Tiny{
    FrameManager::FrameManager()
    :_frameCount(0),
    _targetFps(60),
    _logicalFps(60),
    _currentFrameBeginTime(0.0),
    _lastFrameDelta(0.0){

    }

    void FrameManager::OnFrameBegin(double currentFrameBeginTime, double lastFrameDelta){
      _currentFrameBeginTime = currentFrameBeginTime;
      _lastFrameDelta = lastFrameDelta;
      _frameCount++;

      _realFps = (1 / lastFrameDelta) * 0.9 + _realFps * 0.1;
    }

    void FrameManager::SetLogicalFps(UnsignedByte logicalFps){
      assert(fps > 0);
      _logicalFps = fps;
      _logicalDelta = 1 / logicalFps;
    }

    void FrameManager::SetTargetFps(UnsignedByte fps){
      assert(fps > 0);
      _targetFps = fps;
      _targetDelta = 1 / fps;
    }
}
