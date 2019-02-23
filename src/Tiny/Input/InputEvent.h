#ifndef TINY_CORE_INPUT_BASEINPUTDATA_H
#define TINY_CORE_INPUT_BASEINPUTDATA_H

/*
	Events used by gamelogic
*/
#include "Tiny/Types.h"
#include "IronBranch/Notion/Signals.h" //This file must be included in every header file which has event definition.
#include "Tiny/Input/Interface/Data.h"

namespace Tiny { namespace Input {
	struct KeyboardEvent{
		bool 	holding; //key was pressed before this event.
		bool 	pressed; //key press/release event
		Key		key;
	};

	struct MouseMoveEvent{
		Math::Vector2f 	position; //in screen space coordinate
		Float 			deltaPosition; // relative pos difference from last input. in screen space coordinate
		Float			deltaTime; //in seconds
	};

	struct MouseClickEvent{
		bool		holding;// btn was pressed before this event.
		bool		pressed; //press/release event
		MouseBtn 	button; //left/right btn
	};


	/*
		@brief	Press without movement, triggered by mouse left-button/mobile touch.

	*/
	struct ClickEvent {
		enum class Stage{
			Begin,
			Press,
			Release,
		};
		double	x;
		double	y;
		Stage	stage;
	};

	/*
		@brief	Press with movement, triggered by mouse left-button/mobile touch.

	*/
	struct DragEvent {
		enum class Stage {
			Begin,
			Drag,
			Release,
		};
		double dtX;
		double dtY;
		Stage	stage;
	};


	/*
		@brief	Triggered by keyboard press/release.
	*/
	struct KeyboardEvent {
		enum class Stage{
			Begin,
			Press,
			Release,
		};
		UnsignedInt	key;
		Stage stage;
	};

	/*
		@brief	Triggered by mouse scroll button
	*/
	struct ScrollEvent{
		double x;
		double y;
	};
}
}

#endif // !TINY_CORE_INPUT_BASEINPUTDATA_H
