#include "Camera.h"
#include "Tiny/Core/Service.h"

namespace Tiny {
	namespace Graphics {
		ComponentType comCamera::TYPE = ComponentType::Camera;


		comCamera* comCamera::New(Object* obj)
		{
			if (!obj)
			{
				Service::Log().W("Camera creation failed, obj null");
				return nullptr;
			}

			return new comCamera(obj);
		}

		void comCamera::Destroy(comCamera* camera)
		{
			if (!camera)
				return;

			delete camera;
		}
	}
}