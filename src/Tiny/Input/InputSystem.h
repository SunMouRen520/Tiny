#ifndef TINY_CORE_INPT_INPUTSYSTEM_H
#define TINY_CORE_INPT_INPUTSYSTEM_H

#include "Tiny/Input/BaseInputEvent.h"
#include "IronBranch/Notion/Signals.h"
#include "Tiny/Math/Tools.h"

namespace Tiny { namespace Input {
	struct StandartInput {
		double x;
		double y;

		bool isDragging;

		StandartInput()
			:x(0.0), y(0.0), isDragging(false) {
		}

		StandartInput(double _x, double _y)
			:x(_x), y(_y), isDragging(false) {
		}

		bool Empty() const{
			bool xZero = Math::equals(x, 0.0);
			bool yZero = Math::equals(y, 0.0);
			return xZero && yZero;
		}

		bool operator ==(const StandartInput& other) {
			return std::abs(x - other.x) < 0.1 && std::abs(y - other.y) < 0.1;
		}
	};

	class StandartInputInterface {
	public:
		virtual StandartInput GetStandartInputInfo() const = 0;
	};

	class InputSystem {
	public:
		static InputSystem& Instance() {
			static InputSystem inst;
			return inst;
		}

		/*
		  @brief	Frame update.
		*/
		void Update(double dt);

		void SetStandartInput(StandartInputInterface* input) {
			_plat = input;
		}

		template<typename Object>
		void RegisterClick(Object *obj, void(Object::*func)(const ClickEvent&)) {
			_clickSlots.ConnectMember(obj, func);
		}

		template<typename Object>
		void RegisterDrag(Object *obj, void(Object::*func)(const DragEvent&)) {
			_dragSlots.ConnectMember(obj, func);
		}

	private:
		InputSystem();
		~InputSystem() {}
		InputSystem(const InputSystem&) = delete;

		void ProcessTouch();
		void ProcessTouchEnd();

	private:
		StandartInput _lastFrameInput;
		StandartInput _curFrameInput;
		StandartInputInterface* _plat;
		
		IronBranch::Signals<const ClickEvent&> _clickSlots;
		IronBranch::Signals<const DragEvent&> _dragSlots;
	};
}
}

#endif // !TINY_CORE_INPT_INPUTSYSTEM_H
