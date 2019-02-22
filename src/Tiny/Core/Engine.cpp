#include "Tiny/Core/Engine.h"
#include "Tiny/Input/InputSystem.h"
#include "Tiny/Time.h"

#include <chrono>
#include <thread>

namespace Tiny{
  void Engine::Engine()
  :_frameCount(0){

  }

  void Engine::Init(){
    InputSystem.Instance().Init();
    TimeSystem.Instance().Init();
  }

  /*
    @brief  start the game world.
    @caution:
    游戏主循环采用fixed-stamp模式，逻辑帧以固定间隔更新， 渲染帧以最大帧率更新。
    render world落后logical world一帧， render world采用logical world插值后的结果进行渲染。

         |______|_________|_________|         <-Render frame.
         R1    R2        R3        R4
    |____|____|____|____|____|____|____|      <-Logical frame.
   L1   L2   L3   L4   L5   L6   L7   L8
   渲染时，
   t = (Time(Current Render Frame) - Time(next logical frame)) / Time(logical frame delta)
   Status(Render)  = lerp(Status(last logical frame), Status(current logical frame),  t)
   以Status(Render)的结果进行渲染。(如位置，缩放，角度，透明度等等一切属性)

   Reference discuss:
   1. https://gafferongames.com/post/fix_your_timestep/
   2. http://lspiroengine.com/?p=378
   3. http://www.kinematicsoup.com/news/2016/8/9/rrypp5tkubynjwxhxjzd42s3o034o8
  */
  void Engine::StartUp(){
    double logicalDelta = FrameManager.Instance().GetLogicalFrameDelta();
    double targetDelta = FrameManager.Instance().GetTargetFrameDelta();

    LogicalUpdate();

    double lastTime = Time.GetTime();
    double logicalAccumulator = 0.0;

    //test code for total frame rate control
    double sleepCalibrating = 0.0;

    while(true){
      double currentTime = Time.GetTime();
      double delta = currentTime - lastTime;
      lastTime = currentTime;

      FrameManager.Instance().OnFrameBegin(currentTime, delta);

      //test code for total frame rate control
      sleepCalibrating += targetDelta - delta;
      if(sleepCalibrating > 0){
        double beforeSleep = Time.GetTime();
        std::this_thread::sleep_for(std::chrono::milliseconds((int)(sleepCalibrating * 1000)));
        sleepCalibrating -= Time.GetTime() - beforeSleep;
      }

      logicalAccumulator += delta;
      while(logicalAccumulator >= logicalDelta){
        LogicalUpdate();
        logicalAccumulator -= logicalDelta;
      }

      RenderUpdate();
    }
  }

  /*
    @brief  update logical world.
  */
  void Engine::LogicalUpdate(){
    TimeSystem.Instance().Update();
    InputSystem.Instance().Update();
  }

  /*
    @brief  update render world.
  */
  void Engine::RenderUpdate(){

  }
}
