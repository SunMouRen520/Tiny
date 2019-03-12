#pragma once

#include "Tiny/Input/Module/InputQueue.h"
#include "Tiny/Input/Module/InputModule.h"

namespace Tiny{
    namespace Input{
        class JoypadModule : public InputModule{
        public:
            JoypadModule();

            void Poll() override {}
        private:


		};
    }
}
