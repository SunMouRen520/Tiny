#include "Tiny/Input/Module/KeyboardMouseModule.h"

#include <assert.h>

namespace Tiny{
    namespace Input{
        KeyboardMouseModule::KeyboardMouseModule(UnsignedByte maxKeyCacheNum , UnsignedByte maxMouseCacheNum )
        :InputModule(InputModuleType::KEYBOARD_MOUSE)
        ,_keyboardInput("keyboard", maxKeyCacheNum)
        ,_moustBtn("mousebtn", maxMouseCacheNum)
        ,_mousePos("mousepos",maxMouseCacheNum){
            _curMousePos.push_back(Tiny::Math::Vector2f(0.f, 0.f));
        }

        void KeyboardMouseModule::SetPollTrigger(std::function<void()> pollTrigger){
            _pollTrigger = pollTrigger;
        }

        void KeyboardMouseModule::Pool(){
            if(_pollTrigger)
                _pollTrigger();
        }

        void KeyboardMouseModule::Update(){
            //_lastMouseData = _curMouseData;
            //_lastKeyboardData = _curKeyboardData;
            _lastMousePos = _curMousePos;

            _curKeyboardData = _keyboardInput.Pop();

            _curMousePos = _mousePos.Pop();
            if(_curMousePos.empty()){
                _curMousePos.push_back(_lastMousePos.back());
            }
        }

        const std::list<KeyboardMouseModule::MouseBtnData>&  KeyboardMouseModule::GetCurFrameMouseData() const{
            return _curMouseBtn;
        }

        // const std::list<KeyboardData>& KeyboardMouseModule::GetLastFrameMouseData() const{
        //     return _lastMouseData;
        // }

        const std::list<KeyboardMouseModule::KeyboardData>&  KeyboardMouseModule::GetCurFrameKeyboardData() const{
            return _curKeyboardData;
        }

        // const std::list<KeyboardData>& KeyboardMouseModule::GetLastFrameKeyboardData() const{
        //     return _lastKeyboardData;
        // }

        const std::list<Tiny::Math::Vector2f>&  KeyboardMouseModule::GetMousePos() const{
            return _curMousePos;
        }

        // const std::list<KeyboardData>& KeyboardMouseModule::GetLastFrameMousePos() const{
        //     return _lastMousePos;
        // }

        void KeyboardMouseModule::ReceiveKeyboard(const KeyboardData& d){
            _keyboardInput.Push(d);
        }

        void KeyboardMouseModule::ReceiveMouseBtn(const MouseBtnData &data){
            _moustBtn.Push(data);
        }

        void KeyboardMouseModule::ReceiveMousePos(const Tiny::Math::Vector2f& pos){
            _mousePos.Push(pos);
        }
    }
}
