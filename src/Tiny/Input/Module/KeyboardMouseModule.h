#pragma once

#include "Tiny/Input/Module/InputQueue.h"
#include "Tiny/Input/Module/InputModule.h"
#include "Tiny/Input/Def.h"

#include <functional>

namespace Tiny{
    namespace Input{
		class KeyboardMouseModule : public InputModule{
		public:
            struct KeyboardData{
                KEYBOARD    key;
                bool        pressed;
                bool        holding;
            };

            //当btnMask是SCROLL_UP/SCROLLDOWN时 pressed和pos没有意义
            struct MouseBtnData{
                MOUSEBTN    btn;
                bool        pressed;
                bool        holding;
                Math::Vector2f pos; //in screen coordinate, origin in left-bottom
            };

            KeyboardMouseModule(UnsignedByte maxKeyCacheNum = 100, UnsignedByte maxMouseCacheNum = 10);

            void SetPollTrigger(std::function<void()> pollTrigger);
            void Pool() override;
			void Update();

			void ReceiveKeyboard(const KeyboardData& data);

			void ReceiveMousePos(const Math::Vector2f& pos);
            void ReceiveMouseBtn(const MouseBtnData& data);

			// std::list<KeyboardData>

            const std::list<MouseBtnData>& GetCurFrameMouseData() const;
            // const std::list<MouseData>& GetLastFrameMouseData() const;

            /*
                @brief  If no mouse pos received during this frame, then the last mouse input data will be returned.
            */
            const std::list<Tiny::Math::Vector2f>& GetMousePos() const;

            const std::list<KeyboardData>& GetCurFrameKeyboardData() const;
            // const std::list<KeyboardData>& GetLastFrameKeyboardData() const;

		private:
			InputQueue<KeyboardData> 	_keyboardInput;
			InputQueue<Tiny::Math::Vector2f> 	 _mousePos;
			InputQueue<MouseBtnData> 	     _moustBtn;

            std::list<KeyboardData> _curKeyboardData;
            // std::list<KeyboardData> _lastKeyboardData;
            std::list<MouseBtnData>    _curMouseBtn;
            // std::list<MouseBtnData>    _lastMouseBtn;
            std::list<Tiny::Math::Vector2f> _curMousePos;
            std::list<Tiny::Math::Vector2f> _lastMousePos;

			std::function<void()> 		_pollTrigger;
		};
    }
}
