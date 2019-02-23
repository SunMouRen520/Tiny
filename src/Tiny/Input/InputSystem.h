#ifndef TINY_CORE_INPT_INPUTSYSTEM_H
#define TINY_CORE_INPT_INPUTSYSTEM_H

// #include "Tiny/Core/Input/InputEvent.h"
// #include "Tiny/Core/Input/InputsData.h"

#include "Tiny/Macro.h"
#include "Tiny/Input/Interface/Data.h"

#include "IronBranch/Notion/Signals.h"
#include "Tiny/Math/Tools.h"
#include "Tiny/Math/Vector2.h"
#include "Tiny/Math/MathForward.h"

#include <unordered_map>

namespace Tiny {
	namespace Input {
		class InputSystem {
		public:
			DEF_INSTANCE(InputSystem)

			/*
				@param	threading 	InputBuffer threading
				@param	frequency	if threading enabled, frequency is InputBuffer's polling frequency
			*/
			void Init( bool threading, UnsignedByte frequency);

			void Update();

		private:
			InputSystem() = default;
			void ProcessInput();

		private:
			std::unordered_map<Key, bool> 	_lastTickKeyPress;
			Math::Vector2f					_lastTickMousePos;
		};

		class StandardInputSystem{
		public:
			virtual ~StandardInputSystem() = default;

			void FeedStandInput(const StandardDatum& data) {
				_standardInputs.AddDatum(data);
			}

			virtual void Update(double dt) ;

			// IronBranch::Signals<const ClickEvent&>& OnClick() { return _clickSlots; }
			// IronBranch::Signals<const DragEvent&>& OnDrag() { return _dragSlots; }

		protected:
			StandardInputSystem() {}

		private:
			void Touch(const StandardInputs::Datum& input);
			void TouchEnd();

		private:
			struct InputWithState{
				StandardInputs::Datum	_input;
				bool					_isDragging;

				InputWithState() {
					Clear();
				}

				bool Empty() {
					return _input.x == 0.0 && _input.y == 0.0;
				}

				void Clear() {
					_input.x = 0.0;
					_input.y = 0.0;
					_isDragging = false;
				}

				bool Same(const StandardInputs::Datum& input) {
					return std::abs(_input.x - input.x) < 0.3 && std::abs(_input.y - input.y) < 0.3;
				}
			};

		private:
			// IronBranch::Signals<const ClickEvent&> _clickSlots;
			// IronBranch::Signals<const DragEvent&>	_dragSlots;

			InputWithState	_lastInput;
			StandardInputs	_standardInputs;
		};
	}
}

#endif // !TINY_CORE_INPT_INPUTSYSTEM_H
