#pragma once

#include "Tiny/Input/Module/InputModule.h"
#include "Tiny/Types.h"
#include "Tiny/Input/InputEvent.h"

#include "IronBranch/Notion/Signals.h"

namespace Tiny {
	namespace Input {
		class KeyboardMouseModule;
		class JoypadModule;

		class InputSystem {
		public:
			InputSystem();

			void Update();

			void Poll();

			void AddInputModule(InputModule *input, bool active = true);

			void ActiveInputModule(InputModuleType t);

			void DeactiveInputModule(InputModuleType t);

			void RegisterKeyboard(const std::function<void(const KeyboardEvent&)>& func);
			void RegisterMouseMove(const std::function<void(const MouseMoveEvent&)>& func);
			void RegisterMouseBtn(const std::function<void(const MouseBtnEvent&)>& func);

		private:
			void ProcessKeyboardMouse();
			void ProcessJoyPad();

		private:
			KeyboardMouseModule *_kmModule;
			JoypadModule		*_jpModule;

			InputModuleType	_currentInput;

			IronBranch::Signals<KeyboardEvent> _keyboardEvent;
			IronBranch::Signals<MouseMoveEvent> _mouseMoveEvent;
			IronBranch::Signals<MouseBtnEvent> _mouseBtnEvent;

			Tiny::Math::Vector2f	_lastMousePos;
			Long _posDeltaFrameCount;
		};
	}
}
