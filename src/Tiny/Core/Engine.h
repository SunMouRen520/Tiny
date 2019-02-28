#pragma once

#include "Tiny/Types.h"
#include "Tiny/Def.h"
#include "Tiny/Input/InputSystem.h"
#include "Tiny/Core/FrameManager.h"

namespace Tiny{
    namespace Input{
        class InputSystem;
    }

    class Application;

    class Engine{
    public:
        Engine();
        ~Engine() = default;

        void Init(Application *app);
        void StartUp();
        void ShutDown();

        bool Running() const { return _running;}

        //FIXME: shall we expose inputsystem directly?
        Input::InputSystem& GetInputSystem() {return _input;}

    private:

        void LogicalUpdate();
        void RenderUpdate();

    private:
        Application* _app;
        bool        _running;
        Input::InputSystem _input;
    };
}
