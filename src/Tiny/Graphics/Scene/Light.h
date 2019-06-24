#ifndef _TINY_LIGHT_H
#define _TINY_LIGHT_H

#include "Tiny/Graphics/Object/Component.h"

namespace Tiny {
	namespace Graphics {
		class comLight :public Component
		{
			friend class Object;
		public:
			static ComponentType TYPE;
			comLight(const comLight&) = delete;
			comLight& operator=(const comLight&) = delete;
		private:
			//only called by Object
			static comLight* New(Object*);
			comLight(Object* obj) :Component(ComponentType::Light, obj) {}
		};
	}
}

#endif