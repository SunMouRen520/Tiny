#include "Tiny/Input/InputBuffer.h"
#include "Tiny/Core/Time.h"
#include "Tiny/Core/FrameManager.h"

namespace Tiny{
    namespace Input{
        InputBuffer::InputBuffer()
        :_validDataCount(0)
        ,_pollDelta(10.0f){
            _lastPollTime = Time.GetTime();
        }

        void InputBuffer::Update(){
            if(_threading){
                //此处应获取读写锁的写锁
                std::swap(_readingBufferIndex, _writingBufferIndex);
                _buffers[_writingBufferIndex].Clear();
                //此处应释放读写锁的写锁
            }else{
                _pollDelta = FrameManager.Instance().GetLastFrameDeltaTime() * 1000;
                Poll();
            }
        }

        void InputBuffer::Poll(){
            if(_threading){
                //此处应获取读写锁的写锁
                _pollDelta = Time.GetTime() - _lastPollTime;
            }

            _dataFeeder();
            _buffers[_writingBufferIndex]._validDataCount++;

            if(_threading){
                //此处应释放读写锁的写锁
                _lastPollTime = Time.GetTime();
            }
        }

        void InputBuffer::KeyPress(Key k){
            auto iter = _buffers[_writingBufferIndex]._keyDownUp.find(k)
            if(iter == _buffers[_writingBufferIndex]._keyDownUp.end()){
                iter->second = 1;
            }else{
                iter->second |= 1;
            }
        }

        void InputBuffer::KeyRelease(Key k){
            auto iter = _buffers[_writingBufferIndex]._keyDownUp.find(k)
            if(iter == _buffers[_writingBufferIndex]._keyDownUp.end()){
                iter->second = 2;
            }else{
                iter->second |= 2;
            }
        }

        void InputBuffer::SetMousePos(const InputBuffer::MouseData& data){
            _buffers[_writingBufferIndex]._mousePos.push_back(data);
        }

        void InputBuffer::AddScrollOffset(Short offset){
            _buffers[_writingBufferIndex]._scrollOffset += offset;
        }

        void InputBuffer::AddTouch(const InputBuffer::TouchData& data){
            _buffers[_writingBufferIndex]._touches.push_back(data);
        }
    }
}
