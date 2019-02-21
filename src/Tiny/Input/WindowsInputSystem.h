#ifndef TINY_CORE_INPUT_WINDOWSINPUTSYSTEM_H
#define TINY_CORE_INPUT_WINDOWSINPUTSYSTEM_H

#include "Tiny/Core/Input/InputSystem.h"

namespace Tiny { namespace Input {

	class WindowsInputSystem : public StandardInputSystem {
	public:
		void Update(double dt) override;

		void FeedKeyboardInput(const KeyboardDatum& data) { _keyboardInputs.AddDatum(data); }
		void FeedScrollInput(const ScrollDatum& data) { _scrollInputs.AddDatum(data); }
	protected:
		WindowsInputSystem() {}

	private:
		KeyoardInputs	_keyboardInputs;
		ScrollInputs _scrollInputs;
	};
} }

#endif // !TINY_CORE_INPUT_WINDOWSINPUTSYSTEM_H
