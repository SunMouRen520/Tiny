#pragma once

#include "Tiny/Types.h"
#include "Tiny/Macro.h"

namespace Tiny{
    class Engine{
    public:
        static Engine& Instance(){
            static Engine _inst;
            return _inst;
        }

        void Init();
        void StartUp();
        void ShutDown();

    private:
        Engine();

        void LogicalUpdate();
        void RenderUpdate();

    private:
        FrameManager _frameMgr;
    }
}

#endif
