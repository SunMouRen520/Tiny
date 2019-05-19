#include "Mesh.h"
#include "Tiny/Core/Service.h"

namespace Tiny {
	namespace Graphics {
		ComponentType comMesh::TYPE = ComponentType::Mesh;

		comMesh* comMesh::New(Object* obj)
		{
			if (!obj)
			{
				Service::Log().W("Mesh creation failed, obj null");
				return nullptr;
			}

			return new comMesh(obj);
		}

		void comMesh::Destroy(comMesh* mesh)
		{
			if (!mesh)
				return;

			delete mesh;
		}
	}
}