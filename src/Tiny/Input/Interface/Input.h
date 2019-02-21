#ifndef TINY_INTERFACE_INPUT_INPUT_H
#define TINY_INTERFACE_INPUT_INPUT_H

#include "Tiny/Math/Vector2"
#include "Tiny/Math/MathForward"
#include "Tiny/Input/Interface/Data.h"

namespace Tiny{
  class Input{
  public:
    static Vector2f GetMousePosition(); //get mouse position in screen coordinate
    static Float GetMouseScroll(); //scroll upward is positive
    static bool KeyDown(Key k); //return true if k start pressing during this frame
    static bool KeyUp(Key);
    static bool KeyPress(Key);
    static const TouchData& GetTouch(int index);
  }
}

#endif
