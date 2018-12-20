#ifndef TINY_CORE_INPUT_WINDOWSINPUTSYSTEM_H
#define TINY_CORE_INPUT_WINDOWSINPUTSYSTEM_H

#include "Tiny/Input/InputSystem.h"

namespace Tiny { namespace Input {

	class WindowsInputSystem : public StandardInputSystem {
	public:
		static WindowsInputSystem& Instance();

		void Update(double dt) override;

		//template<typename UnderlyingSystem>
		//void SetKeyboardFetchInterface(UnderlyingSystem* sys, KeyoardInputs&(UnderlyingSystem::*fetch)(void) ) {
		//	_keyboardFetch = [=]() -> KeyoardInputs&{
		//		return (sys->*fetch)();
		//	};
		//}

		//template<typename UnderlyingSystem>
		//void SetScrollFetchInterface(UnderlyingSystem* sys, ScrollInputs&(UnderlyingSystem::*fetch)(void) ) {
		//	_scrollFetch = [=]() -> ScrollInputs&{
		//		return (sys->*fetch)();
		//	};
		//}

		void FeedKeyboardInput(const KeyboardDatum& data) { _keyboardInputs.AddDatum(data); }
		void FeedScrollInput(const ScrollDatum& data) { _scrollInputs.AddDatum(data); }


		IronBranch::Signals<const KeyboardEvent&>& OnKeyboard(){
			return _keyboardSlots;
		}


		IronBranch::Signals<const ScrollEvent&>& OnScroll(){
			return _scrollSlots;
		}

	protected:
		WindowsInputSystem() {}

	private:
		//std::function<KeyoardInputs&()>	_keyboardFetch;
		//std::function<ScrollInputs&()>	_scrollFetch;

		IronBranch::Signals<const KeyboardEvent&>		_keyboardSlots;
		IronBranch::Signals<const ScrollEvent&>		_scrollSlots;
		KeyoardInputs	_keyboardInputs;
		ScrollInputs _scrollInputs;
	};

	//struct KeyboardEvent {
	//	std::uint32_t keyboard; //using GLFW keyboard macro value

	//	KeyboardEvent() :keyboard(-1) {}

	//	bool Valid(){ return keyboard != -1; }
	//	void SetInvalid() { keyboard = -1; }
	//};

	//struct ScrollEvent {
	//	double x;
	//	double y;

	//	ScrollEvent() :x(0), y(0) {}

	//	bool Valid() {
	//		return x || y;
	//	}
	//	void SetInvalid() {
	//		x = 0;
	//		y = 0;
	//	}
	//};

	/*class WindowsInputInterface : public StandartInputInterface {
	public:
		virtual ScrollEvent GetScrollEvent() const = 0 ;
		virtual KeyboardEvent GetKeyboardEvent() const = 0 ;
	};

	class WindowsInputSystem : public InputSystem {
		friend class InputSystem;

	public:
		void Update(double dt) override;

		void SetStandartInput(WindowsInputInterface* input) {
			InputSystem::SetStandartInput(input);
			_window = input;
		}

		template<typename Object>
		void RegisterMouseScroll(Object *obj, void(Object::*func)(const ScrollEvent&)) {
			_scrollSlots.ConnectMember(obj, func);
		}

		template<typename Object>
		void RegisterKeyboardEvent(Object *obj, void(Object::*func)(const KeyboardEvent&)) {
			_keyboardSlots.ConnectMember(obj, func);
		}

	protected:
		WindowsInputSystem() = default;
		~WindowsInputSystem() = default;

	private:
		IronBranch::Signals<ScrollEvent> _scrollSlots;
		IronBranch::Signals<KeyboardEvent> _keyboardSlots;
		WindowsInputInterface* _window;
	};*/
} }

#endif // !TINY_CORE_INPUT_WINDOWSINPUTSYSTEM_H
