#ifndef _TINY_MESH_H
#define _TINY_MESH_H

#include "../Object/Component.h"

namespace Tiny {
	namespace Graphics {
		class comMesh :public Component
		{
			friend class Object;
		public:
			static ComponentType TYPE;
			comMesh(const comMesh&) = delete;
			comMesh& operator=(const comMesh&) = delete;
		private:
			//only called by Object
			static comMesh* New(Object*);
			static void Destroy(comMesh*);
			comMesh(Object* obj) :Component(ComponentType::Mesh, obj) {}
		};
	}
}

#endif