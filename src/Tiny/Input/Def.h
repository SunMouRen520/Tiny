#pragma once

#include "Tiny/Types.h"
#include "Tiny/Math/Vector2.h"
#include "Tiny/Math/MathForward.h"

namespace Tiny{
    namespace Input{
        constexpr UnsignedByte MaxTouchCount = 5;
        enum class KEYBOARD: UnsignedByte{
            INVALID = 0,

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

            F1,
            F2,
            F3,
            F4,
            F5,
            F6,
            F7,
            F8,
            F9,
            F10,
            F11,
            F12,

            KEY_0,
            KEY_1,
            KEY_2,
            KEY_3,
            KEY_4,
            KEY_5,
            KEY_6,
            KEY_7,
            KEY_8,
            KEY_9,

            ESC,
            TAB,
            CAPSLOCK,
            LEFTSHIFT,
            LEFTCTRL,
            LEFTALT,
            RIGHTSHIFT,
            RIGHTCONTROL,
            RIGHTALT,
            BACKSPACE,
            ENTER,
            LEFTBRACKET,
            RIGHTBRACKET,
            SEMICOLON,
            APOSTROPHE,
            COMMA,
            PERIOD,
            SLASH,
            BACKSLASH,
			SPACE,

            RIGHT,
            LEFT,
            DOWN,
            UP,

            COUNT,
        };

        enum class MOUSEBTN : UnsignedShort{
            INVALID = 0,

            MOUSE_LEFT_BTN = 1 << 0,
            MOUSE_RIGHT_BTN = 1 << 1,
            MOUSE_MIDDLE_BTN = 1 << 2,
            MOUSE_MIDDLE_BTN_SCROLL_UP = 1 << 3,
            MOUSE_MIDDLE_BTN_SCROLL_DOWN = 1 << 4,
        };
    }
}
