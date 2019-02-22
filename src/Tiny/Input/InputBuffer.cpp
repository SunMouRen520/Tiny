#include "Tiny/Input/InputBuffer.h"


namespace Tiny{
  namespace Input{
    void InputBuffer::Update(){
      if(_threading){
        //此处应获取读写锁的写锁
        std::swap(_readingBufferIndex, _writingBufferIndex);
        _writingBufferIndex.Clear();
        //此处应释放读写锁的写锁
      }else{
        Poll();
      }
    }

    void InputBuffer::Poll(){
      if(_threading){
        //此处应获取读写锁的写锁
      }
      _dataFeeder();
      if(_threading){
        //此处应释放读写锁的写锁
      }
    }

    /*所有的set操作应该都是通过_dataFeeder进行，所以不应该再set内再加锁  */
    void InputBuffer::KeyPress(Key k){
      auto iter = _buffers[_writingBufferIndex]._keyDown.find(k)
      if(iter == _buffers[_writingBufferIndex]._keyDown.end()){
        iter->second = 1;
      }else{
        iter->second |= 1;
      }
    }

    void InputBuffer::KeyRelease(Key k){
      auto iter = _buffers[_writingBufferIndex]._keyDown.find(k)
      if(iter == _buffers[_writingBufferIndex]._keyDown.end()){
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
