#ifndef _TINY_COMPONENT_H
#define _TINY_COMPONENT_H

namespace Tiny {
	namespace Graphics {
		enum class ComponentType
		{
			Transform,
			Mesh,
			Camera,
			Light,
		};
		class Object;
		class Component
		{
		public:
			Component(ComponentType comtype, Object* objptr = nullptr) :type(comtype), object(objptr) {};
			~Component() = default;

			ComponentType Type() const { return type; };
			Object* GameObject() const { return object; };
		private:
			ComponentType type;
			Object* object;
		};
	}
}

#endif