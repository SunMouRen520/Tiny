#include "Light.h"
#include "Tiny/Core/Service.h"

namespace Tiny {
	namespace Graphics {
		ComponentType comLight::TYPE = ComponentType::Light;

		comLight* comLight::New(Object* obj)
		{
			if (!obj)
			{
				Service::Log().W("Light creation failed, obj null");
				return nullptr;
			}

			return new comLight(obj);
		}

		void comLight::Destroy(comLight* light)
		{
			if (!light)
				return;

			delete light;
		}
	}
}