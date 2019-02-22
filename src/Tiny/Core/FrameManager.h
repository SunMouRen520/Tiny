#pragma once

namespace Tiny{
  class Engine;
  /*
    Frame:
    1. logical fps 和 fps target在游戏初始化时就设置好 且在游戏运行过程中不变
  */
  class FrameManager{
    friend class Engine;
  public:
    DEF_INSTANCE(FrameManager);

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
      @brief  get total fps target
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
    */
    Float GetLastFrameDeltaTime() const { return _lastFrameDelta; }

    /*
      @brief  get current frame begin time(real time).(constant through whole frame)
    */
    Float GetFrameBeginTime() const { return _currentFrameBeginTime;}

    /*
      @brief  Get frame count since start up.
    */
    Int GetFrameCount() const { return _frameCount;}

  protected:
    void OnFrameBegin(double currentFrameBeginTime, double lastFrameDelta);

  private:
    FrameManager();

  private:
    Int _frameCount;

    UnsignedByte  _targetFps;
    Double        _targetDelta;
    UnsignedByte  _logicalFps;
    Double        _logicalDelta;

    double  _realFps;

    double _currentFrameBeginTime;
    double _lastFrameDelta;
  };
}
