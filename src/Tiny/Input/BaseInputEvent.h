#ifndef TINY_CORE_INPUT_BASEINPUTDATA_H
#define TINY_CORE_INPUT_BASEINPUTDATA_H

namespace Tiny { namespace Input {

	/*
		@brief	
				
	*/
	struct ClickEvent {
		enum class ClickType {
			Press,
			Release,
		};
		double x;
		double y;
		ClickType type;
	};

	struct DragEvent {
		enum class DragType {
			Begin,
			Drag,
			Release,
		};
		double dtX;
		double dtY;
		DragType type;
	};
}
}

#endif // !TINY_CORE_INPUT_BASEINPUTDATA_H

