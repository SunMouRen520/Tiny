#include "Tiny/Core/Engine.h"
#include "Tiny/Input/InputSystem.h"

namespace Tiny{
  void Engine::Engine()
  :_frameCount(0){

  }

  void Engine::Init(){
    InputModule.Instance().Init();
  }

  void Engine::StartUp(){
    while(true){
      _frameMgr.Forward();

    }
  }
}
