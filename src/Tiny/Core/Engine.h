#ifndef TINY_CORE_ENGINE_H
#deifne TINY_CORE_ENGINE_H

#include "Tiny/Types.h"

namespace Tiny{
  class Engine;
  class FrameManager{
    friend class Engine;
  public:
    /*
      @brief  set fphHint as target fps, which may not be the real fps due to each tick may take too long time and so on.
    */
    void SetFps(UnsignedByte fpsHint);
    UnsignedByte GetFps() const;

  protected:
    void StepForward(){
      _frameCount++;
    }

  private:
    Int _frameCount;
    UnsignedByte _fps;

  };

  class Engine{
  public:
    static Engine& Instance(){
      static Engine _inst;
      return _inst;
    }

    void Init();
    void StartUp();
    void ShutDown();

    Int GetFrameCount(){
      return _frameCount;
    }

  protected:
    Engine();

  private:
    FrameManager _frameMgr;
  }
}

#endif
