#include "Tiny/Input/WindowsInputSystem.h"


namespace Tiny { namespace Input {
	WindowsInputSystem& WindowsInputSystem::Instance() {
		static WindowsInputSystem inst;

		return inst;
	}

	void WindowsInputSystem::Update(double dt) {
		StandardInputSystem::Update(dt);

		for (auto& scrollData : _scrollInputs) {
			ScrollEvent event = { scrollData.x, scrollData.y };
			_scrollSlots.Emit(event);
		}
		_scrollInputs.Clear();

		for (auto& data: _keyboardInputs) {
			KeyboardEvent event;
			event.key = data.keyboard;
			event.stage = data.type == KeyboardDatum::Type::Rlease ? KeyboardEvent::Stage::Release : KeyboardEvent::Stage::Press;
			_keyboardSlots.Emit(event);
		}
		_keyboardInputs.Clear();
	}
} }
