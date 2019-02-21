#ifndef TINY_CORE_INPT_INPUTSYSTEM_H
#define TINY_CORE_INPT_INPUTSYSTEM_H

// #include "Tiny/Core/Input/InputEvent.h"
// #include "Tiny/Core/Input/InputsData.h"

#include "Tiny/Input/Interface/Data.h"

#include "IronBranch/Notion/Signals.h"
#include "Tiny/Math/Tools.h"
#include "Tiny/Math/Vector2.h"
#include "Tiny/Math/MathForward.h"

#include <unordered_map>

namespace Tiny {
	namespace Input {
		class InputBuffer{
		public:
			struct TouchData{
				Vector2f pos;
				Int fingerId;
			};

			DEF_INSTANCE(InputBuffer)

			void Init(std::function<void()> dataFeeder,  bool threading, UnsignedByte frequency = 120){
				_dataFeeder = dataFeeder;
			}

			void ReadLock();
			void ReleaseReadLock();

			void AddKeyPress(Key k);
			void AddKeyRelease(Key k);
			void SetMousePos(const Vector2f& pos);
			void AddScrollOffset(Short offset);
			void AddTouch(const InputBuffer::TouchData& data);

			bool Threading() const {
				return _threading;
			}

			void Tick(double dt){
				_dataFeeder();
			}

		private:
			void GetLock();

		private:
			std::function<void()> _dataFeeder;
			bool _threading; //run

		};

		class InputModule {
		public:
			static InputModule& Instance(){
				static InputModule _inst;
				return _inst;
			}

			void Init( bool threading, UnsignedByte frequency){

			}

			void Tick(double dt){
				if(!InputBuffer.Instance().Threading())
					InputBuffer.Instance().Tick(dt);

			}

			void

		private:
			InputModule();

		private:
			std::unordered_map<Key, bool> _keyDown;
			std::unordered_map<Key, bool> _keyUp;
			std::unordered_map<Key, bool> _keyPress;
			Math::Vector2f _mousePos;
			Short _scrollOffset;

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
