#ifndef TINY_CORE_INPUT_BASEINPUTDATA_H
#define TINY_CORE_INPUT_BASEINPUTDATA_H

/*
	Events used by gamelogic
*/
#include "Tiny/Types.h"

namespace Tiny { namespace Input {

	/*
		@brief	Press without movement, triggered by mouse left-button/mobile touch.
				
	*/
	struct ClickEvent {
		enum class Stage{
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

