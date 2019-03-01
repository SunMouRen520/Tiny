#include "Tiny/Input/InputSystem.h"
#include "Tiny/Input/Module/KeyboardMouseModule.h"
#include "Tiny/Input/Module/JoypadModule.h"
#include "Tiny/Input/InputEvent.h"

#include "Tiny/Core/Service.h"
#include "Tiny/Math/Tools.h"

#include <assert.h>
#include <sstream>

namespace Tiny {
	namespace Input {
		InputSystem::InputSystem()
			:_kmModule(nullptr)
			, _jpModule(nullptr)
			, _currentInput(InputModuleType::INVLIAD)
			, _lastMousePos(-1.f, -1.f) {
			// _currentInput = km->GetType();
			// AddInputModule(input);
		}

		void InputSystem::AddInputModule(InputModule *input, bool active) {
			switch (input->GetType()) {
			case InputModuleType::KEYBOARD_MOUSE:
				_kmModule = dynamic_cast<KeyboardMouseModule*>(input);
				if (!_kmModule) {
					Service::Log().E("InputModule cast from Base to KeyboardMouseModule failed");
					assert(false);
				}
				break;
			case InputModuleType::JOYPAD:
				_jpModule = dynamic_cast<JoypadModule*>(input);
				if (!_jpModule) {
					Service::Log().E("InputModule cast from Base to JoypadModuel failed");
					assert(false);
				}
				break;
			}

			if (active)
				ActiveInputModule(input->GetType());
		}

		void InputSystem::ActiveInputModule(InputModuleType t) {
			_currentInput |= t;
		}

		void InputSystem::DeactiveInputModule(InputModuleType t) {
			_currentInput &= ~t;
		}

		void InputSystem::Update() {
			if ((_currentInput | InputModuleType::KEYBOARD_MOUSE) != InputModuleType::INVLIAD)
				ProcessKeyboardMouse();

			if ((_currentInput | InputModuleType::JOYPAD) != InputModuleType::INVLIAD)
				ProcessKeyboardMouse();
		}

		void InputSystem::Pool() {
			if ((_currentInput | InputModuleType::KEYBOARD_MOUSE) != InputModuleType::INVLIAD)
				_kmModule->Pool();

			if ((_currentInput | InputModuleType::JOYPAD) != InputModuleType::INVLIAD)
				_jpModule->Pool();
		}

		void InputSystem::ProcessKeyboardMouse() {
			_kmModule->Update();

			const std::list<KeyboardMouseModule::KeyboardData> &curKeys = _kmModule->GetCurFrameKeyboardData();
			for (const KeyboardMouseModule::KeyboardData& iter : curKeys) {
				KeyboardEvent e;
				e.holding = iter.holding;
				e.pressed = iter.pressed;
				e.key = iter.key;

				Service::Log().V("Input: {}", iter);
				_keyboardEvent.Emit(e);
			}

			const std::list<KeyboardMouseModule::MouseBtnData>  &curMice = _kmModule->GetCurFrameMouseData();
			for (const auto& iter : curMice) {
				MouseBtnEvent m;
				m.holding = iter.holding;
				m.pressed = iter.pressed;
				m.button = iter.btn;
				m.position = iter.pos;
				Service::Log().V("Input: {}", iter);
				_mouseBtnEvent.Emit(m);
			}

			const std::list<Tiny::Math::Vector2f> &mousePos = _kmModule->GetMousePos();
			if (_lastMousePos.X() == -1.f) {
				_lastMousePos = mousePos.front();
				_posDeltaFrameCount = Service::FrameManager().GetLogicalFrameCount();
			}

			for (const auto& iter : mousePos) {
				if (!(iter == _lastMousePos)) {
					Long newPosFrameCount = Service::FrameManager().GetLogicalFrameCount();
					double dt = 0;
					if (newPosFrameCount == _posDeltaFrameCount) {
						dt = Service::FrameManager().GetLogicalFrameDelta() / mousePos.size();
					}
					else {
						dt = Service::FrameManager().GetLogicalFrameDelta() * (newPosFrameCount - _posDeltaFrameCount);
						_posDeltaFrameCount = newPosFrameCount;
					}
					MouseMoveEvent m;
					m.position = iter;
					m.deltaPosition = iter - _lastMousePos;
					//FIXME::�޷��ڴ˴��������Ժ�����deltatime��
					m.deltaTime = (float)dt;
					Service::Log().V("Input: MouseMove: {}, deltaPosition:{}, dt:{}", m.position, m.deltaPosition, m.deltaTime);
					_lastMousePos = iter;
				}
			}
		}

		void InputSystem::RegisterKeyboard(const std::function<void(const KeyboardEvent&)>& func) {
			_keyboardEvent.Connect(func);
		}
		void InputSystem::RegisterMouseMove(const std::function<void(const MouseMoveEvent&)>& func) {
			_mouseMoveEvent.Connect(func);
		}
		void InputSystem::RegisterMouseBtn(const std::function<void(const MouseBtnEvent&)>& func) {
			_mouseBtnEvent.Connect(func);
		}

		void InputSystem::ProcessJoyPad() {

		}
} }
