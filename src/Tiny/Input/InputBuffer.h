#pragma once

#include "Tiny/Macro.h"
#include "Tiny/Types.h"
#include "Tiny/Input/Interface/Data.h"

#include <unordered_map>
#include <list>

namespace Tiny{
  namespace Input{
    /*
      @brief  外界输入input数据的缓存
    */
    class InputBuffer{
    public:
      DEF_INSTANCE(InputBuffer)

      struct InputData{
        Long touchId;
        Vector2f pos;
      };

      struct MouseData{
        Vector2f pos;
        UnsignedByte mask; // 1: left btn press. 2: right btn press 4:middle btn press.
      };

      void Init(std::function<void()> dataFeeder,  bool threading, UnsignedByte frequency = 120){
        _dataFeeder = dataFeeder;
        _threading = threading;
        _frequency = frequency;
      }

      void KeyPress(Key k);
      void KeyRelease(Key k);
      void SetMousePos(const InputBuffer::MouseData& data);
      /*
        @brief  offset is positive when scroll upward.
      */
      void AddScrollOffset(Short offset);
      /*
        @brief  only data.touchId and data.position are needed, remain properties will be calculated by InputBuffer.
      */
      void AddTouch(const InputBuffer::TouchData& data);

      /*
        @brief  poll input data
      */
      void Poll();

      void Update();

      const std::list<InputBuffer::TouchData>& GetTouches(){ return _touches;}
      const std::unordered_map<Key, UnsignedByte>& GetKeyDownUp() {return }

    private:
      std::function<void()> _dataFeeder;
      bool _threading; //running in seperate thread.
      UnsignedByte _frequency ; //threading loop frequency

      struct FrameKeyBuffer{
        //UnsignedByte是mask, 1表示down, 2表示up
        std::unordered_map<Key, UnsignedByte> _keyDownUp;
        std::list<MouseData>          	        _mousePos;
        Short 												        _scrollOffset;
        std::list<InputBuffer::TouchData>                  _touches;

        void Clear(){
          _keyDownUp.clear();
          _mousePos.clear();
          _scrollOffset = 0;
          _touches.Clear();
        }
      };

      FrameKeyBuffer	_buffers[2];
      UnsignedByte		_readingBufferIndex;
      UnsignedByte		_writingBufferIndex;
    };
  }
}
