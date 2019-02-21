#include "Tiny/Core/Input/WindowsInputSystem.h"
#include "Tiny/Core/Input/InputEvent.h"

namespace Tiny { namespace Input {
	void WindowsInputSystem::Update(double dt) {
		StandardInputSystem::Update(dt);

		for (auto& scrollData : _scrollInputs) {
			ScrollEvent event = { scrollData.x, scrollData.y };
			IronBranch::GetEventSignal<ScrollEvent>().Emit(event);
		}
		_scrollInputs.Clear();

		for (auto& data: _keyboardInputs) {
			KeyboardEvent event;
			event.key = data.keyboard;
			event.stage = data.type == KeyboardDatum::Type::Rlease ? KeyboardEvent::Stage::Release : KeyboardEvent::Stage::Press;
			IronBranch::GetEventSignal<KeyboardEvent>().Emit(event);
		}
		_keyboardInputs.Clear();
	}
} }
