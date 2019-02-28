#pragma once

#include "Tiny/Types.h"

namespace Tiny{
    namespace Input{
		enum class InputModuleType : UnsignedByte {
			INVLIAD = 0,
			KEYBOARD_MOUSE = 1 << 0,
			TOUCH = 1 << 1,//not implement yet
			JOYPAD = 1 << 2 //not implement yet

		};
		inline InputModuleType operator|(InputModuleType a, InputModuleType b) {
			return static_cast<InputModuleType>(static_cast<UnsignedByte>(a) | static_cast<UnsignedByte>(b));
		}

		inline InputModuleType operator ~ (InputModuleType a) {
			return static_cast<InputModuleType>(~(static_cast<UnsignedByte>(a)));
		}

		inline void operator &=(InputModuleType a, InputModuleType b) {
			a = static_cast<InputModuleType>(static_cast<UnsignedByte>(a) & static_cast<UnsignedByte>(b));
		}

		inline void operator|=(InputModuleType a, InputModuleType b) {
			a = a | b;
		}

        class InputModule{
        public:
            InputModule(InputModuleType type)
            :_type(type){

            }

            virtual ~InputModule() = default;

            InputModuleType GetType() const {return _type;}

            virtual void Pool() = 0;
        private:
            InputModuleType _type;
        };
    }
}
