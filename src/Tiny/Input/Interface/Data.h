#ifndef TINY_INTERFACE_INPUT_DATA_H
#define TINY_INTERFACE_INPUT_DATA_H

#include "Tiny/Types.h"
#include "Tiny/Math/Vector2.h"
#include "Tiny/Math/MathForward.h"

namespace Tiny{
  namespace Input{

    enum class Key{
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

      MOUSE_LEFT_BTN,
      MOUSE_RIGHT_BTN,
      MOUSE_MIDDLE_BTN,
    };

    enum class TouchPhase{
      Begin,
      Press,
      Release,
    };

    struct TouchData{
      Math::Vector2f  position;
      TouchPhase      phase;
      Long            touchId;
      Math::Vector2f  deltaPosition;
      Float           deltaTime;
    };
  }
}

#endif
