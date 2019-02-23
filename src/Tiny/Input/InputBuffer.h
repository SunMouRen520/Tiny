#pragma once

#include "Tiny/Macro.h"
#include "Tiny/Types.h"
#include "Tiny/Input/Interface/Data.h"

#include <unordered_map>
#include <list>
#include <bitset>

namespace Tiny{
    namespace Input{
        /*
        @brief  外界输入input数据的缓存
        */
        constexpr UnsignedByte MaxBufferCount = 10;
        class InputBuffer{
        public:
            DEF_INSTANCE(InputBuffer)

            struct TuchData{
                Long touchId;
                Vector2f pos;

                void Clear(){
                    touchId = -1;
                }

                bool Valid() {
                    return touchId != -1;
                }
            };

            struct MouseData{
                Vector2f pos;
                UnsignedByte mask; // 1: left btn press. 2: right btn press 4:middle btn press.
            };

            void Init(bool threading, UnsignedByte frequency = 120){
                _threading = threading;
                _frequency = frequency;
            }

            void SetDataFeeder(std::function<void()> dataFeeder){
                _dataFeeder = dataFeeder;
            }

            void KeyPress(KEYBOARD k);
            void MouseBtn(MOUSEBTN m);
            void SetMousePos(const InputBuffer::MouseData& data);
            /*
            @brief  only data.touchId and data.position are needed, remain properties will be calculated by InputBuffer.
            */
            void AddTouch(const InputBuffer::TouchData& data);

            /*
            @brief  poll input data
            */
            void Poll();

            /*
            @brief  get the interval time(in milliseconds) of last poll.
            */
            Float GetPollDeltaInMilliSec();

            void Update();

            const std::list<InputBuffer::TouchData>& GetTouches() const{ return _buffers[_readingBufferIndex]._touches;}

            const std::unordered_map<Key, bool>& GetKeyDown() const {return _buffers[_readingBufferIndex]._keyDownUp;}

            Short GetScrollOffset() const {return _scrollOffset;}

            const std::list<MouseData>& GetMouseData const{ return _mousePos;}

        private:
            InputBuffer();
            ~InputBuffer() = default;

        private:
            std::function<void()> _dataFeeder;
            bool _threading; //running in seperate thread.
            UnsignedByte _frequency ; //threading loop frequency

            class TickFrameData{
            public:
                TickFrameData() = default;
                ~TickFrameData = default;

                void Tick(){
                    _validDataCount++;
                    if(_validDataCount >= MaxBufferCount){
                        _validDataCount = MaxBufferCount - 1;
                        
                    }
                }

            private:
                struct Data{
                    std::bitset<KEYBOARD::COUNT> _keys; //bit setting to 1 means the corresponding key was pressed
                    std::bitset<MOUSE::COUNT> _mouse;//bit setting to 1 means the corresponding moust btn was pressed
                    Math::Vector2f    _mousePos;

                    InputBuffer::TouchData[MaxTouchCount] _touches;

                    void Clear(){
                        _keys.reset();
                        _mouse.reset();
                        for(auto& touch : _touches)
                            touch.Clear();
                        _validDataCount = 0;
                    }
                };

                Data   _buffer[MaxBufferCount];
                UnsignedByte _validDataCount = 0;
            };

            TickFrameData _buffers[2];

            UnsignedByte		_readingBufferIndex;
            UnsignedByte		_writingBufferIndex;

            Float             _lastPollTime;
            Float             _pollDelta; // in milliseconds
        };
    }
}
