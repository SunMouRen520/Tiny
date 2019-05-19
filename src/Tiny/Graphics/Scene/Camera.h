#ifndef _TINY_CAMERA_H
#define _TINY_CAMERA_H

#include "../Object/Component.h"

namespace Tiny {
	namespace Graphics {
		class comCamera :public Component
		{
			friend class Object;
		public:
			static ComponentType TYPE;
			comCamera(const comCamera&) = delete;
			comCamera& operator=(const comCamera&) = delete;
		private:
			//only called by Object
			static comCamera* New(Object*);
			static void Destroy(comCamera*);
			comCamera(Object* obj) :Component(ComponentType::Camera, obj) {}
		};
	}
}

#endif