#ifndef TINY_INTERFACE_INPUT_DATA_H
#define TINY_INTERFACE_INPUT_DATA_H

#include "Tiny/Types.h"
#include "Tiny/Math/Vector2.h"
#include "Tiny/Math/MathForward.h"

namespace Tiny{
    namespace Input{
        constexpr UnsignedByte MaxTouchCount = 5;
        enum class KEYBOARD: UnsignedByte{
            None = 0,

            KEY_A,
            KEY_B,
            KEY_C,
            KEY_D,
            KEY_E,
            KEY_F,
            KEY_G,
            KEY_H,
            KEY_I,
            KEY_J,
            KEY_K,
            KEY_L,
            KEY_M,
            KEY_N,
            KEY_O,
            KEY_P,
            KEY_Q,
            KEY_R,
            KEY_S,
            KEY_T,
            KEY_U,
            KEY_V,
            KEY_W,
            KEY_X,
            KEY_Y,
            KEY_Z,

            f1,
            f2,
            f3,
            f4,
            f5,
            f6,
            f7,
            f8,
            f9,
            f10,
            f11,
            f12,

            ESC,
            TILDE,
            TAB,
            CAPSLOCK,
            LEFTSHIFT,
            LEFTCTRL,
            BACKSPACE,
            ENTER,
            LEFTBRACKET,
            RIGHTBRACKET,
            SEMICOLON,
            QUOTE,
            COMMA,
            PERIOD,
            SLASH,
            BACKSLASH,

            COUNT,
        };

        enum class MOUSEBTN{
            MOUSE_LEFT_BTN,
            MOUSE_RIGHT_BTN,
            MOUSE_MIDDLE_BTN,
            MOUSE_MIDDLE_BTN_SCROLL_UP,
            MOUSE_MIDDLE_BTN_SCROLL_DOWN,
            COUNT,
        };

        enum class InputPhase{
            Begin,
            Press,
            Release,
        };

        struct PointerData{
            Math::Vector2f  position;
            Math::Vector2f  deltaPosition;
            Float           deltaTime;
        };

        struct TouchData : public PointerData{
            InputPhase      phase;
            Long            touchId;
        };

        struct MouseData : public PointerData{
            InputPhase      phase[3]; //0:left btn, 1:right btn, 2:middle btn
        };
    }
}

#endif
