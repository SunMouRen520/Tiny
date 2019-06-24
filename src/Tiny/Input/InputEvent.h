#pragma once

#include "Tiny/Types.h"
#include "IronBranch/Notion/Signals.h" //This file must be included in every header file which has event definition.
#include "Tiny/Input/Def.h"

namespace Tiny { namespace Input {
	struct KeyboardEvent{
		bool 	holding; //key was pressed before this event.
		bool 	pressed; //key press/release event
		KEYBOARD		key;
	};

	struct MouseMoveEvent{
		Math::Vector2f 	position; //in screen space coordinate
		Math::Vector2f deltaPosition; // relative pos difference from last input. in screen space coordinate
		Float			deltaTime; //in seconds
	};

	struct MouseBtnEvent{
		bool		holding;// btn was pressed before this event.
		bool		pressed; //press/release event
		MOUSEBTN 	button; //left/right btn
		Math::Vector2f position; //in screen space coordinate
		Math::Vector2f deltaPosition; //the delta pos of mouse moved in holding state
 	};
}
}
