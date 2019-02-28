#include "Tiny/Core/FrameManager.h"

#include <assert.h>

namespace Tiny{
    FrameManager::FrameManager()
    :_frameCount(0),
    _currentFrameBeginTime(0.0){
        _lastFrameDelta = 1 / _targetFps;
        SetLogicalFps(60);
        SetTargetFps(60);
    }

    void FrameManager::OnFrameBegin(double currentFrameBeginTime, double lastFrameDelta){
      _currentFrameBeginTime = currentFrameBeginTime;
      _lastFrameDelta = lastFrameDelta;
      _frameCount++;

      _realFps = (1.0 / lastFrameDelta) * 0.9 + _realFps * 0.1;
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
}
