#ifndef TINY_CORE_INPT_INPUTSYSTEM_H
#define TINY_CORE_INPT_INPUTSYSTEM_H

#include "Tiny/Input/InputQueue.h"

//TODO:不要直接使用Ironbran的signal，需要在tiny加一层事件逻辑 以保证事件都是在logicalupdate中触发。
// #include "IronBranch/Notion/Signals.h"
// #include "Tiny/Math/Tools.h"
// #include "Tiny/Math/Vector2.h"
// #include "Tiny/Math/MathForward.h"

// #include <unordered_map>

namespace Tiny {
	namespace Input {
		class KeyboardMouseSerice{
		public:
			void SetPollFunction(std::function<void()> pollFunc);
			void Poll();

		private:
			InputQueue<KeyboardData> _keyboardInput;
			InputQueue<MouseBtnData> _mouseBtnInput;
			InputQueue<Math::Vector2f>	_mousePosInput;
		};

		class InputSystem {
		public:
			/*
				@param	threading 	InputBuffer threading
				@param	frequency	if threading enabled, frequency is InputBuffer's polling frequency
			*/


			void Update();

		private:
			InputSystem() = default;
			void ProcessInput();

		private:
		};

		// class StandardInputSystem{
		// public:
		// 	virtual ~StandardInputSystem() = default;
		//
		// 	void FeedStandInput(const StandardDatum& data) {
		// 		_standardInputs.AddDatum(data);
		// 	}
		//
		// 	virtual void Update(double dt) ;
		//
		// 	// IronBranch::Signals<const ClickEvent&>& OnClick() { return _clickSlots; }
		// 	// IronBranch::Signals<const DragEvent&>& OnDrag() { return _dragSlots; }
		//
		// protected:
		// 	StandardInputSystem() {}
		//
		// private:
		// 	void Touch(const StandardInputs::Datum& input);
		// 	void TouchEnd();
		//
		// private:
		// 	struct InputWithState{
		// 		StandardInputs::Datum	_input;
		// 		bool					_isDragging;
		//
		// 		InputWithState() {
		// 			Clear();
		// 		}
		//
		// 		bool Empty() {
		// 			return _input.x == 0.0 && _input.y == 0.0;
		// 		}
		//
		// 		void Clear() {
		// 			_input.x = 0.0;
		// 			_input.y = 0.0;
		// 			_isDragging = false;
		// 		}
		//
		// 		bool Same(const StandardInputs::Datum& input) {
		// 			return std::abs(_input.x - input.x) < 0.3 && std::abs(_input.y - input.y) < 0.3;
		// 		}
		// 	};
		//
		// private:
		// 	// IronBranch::Signals<const ClickEvent&> _clickSlots;
		// 	// IronBranch::Signals<const DragEvent&>	_dragSlots;
		//
		// 	InputWithState	_lastInput;
		// 	StandardInputs	_standardInputs;
		// };
	}
}

#endif // !TINY_CORE_INPT_INPUTSYSTEM_H
