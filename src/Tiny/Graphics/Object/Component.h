#ifndef _TINY_COMPONENT_H
#define _TINY_COMPONENT_H

namespace Tiny {
	namespace Graphics {
		enum class ComponentType
		{
			Transform,
			Mesh,
			SkinedMesh,
			Camera,
			Light,
		};
		class Object;
		class Component
		{
		public:
			Component(ComponentType comtype, Object* objptr = nullptr) :type(comtype), object(objptr) {};
			virtual ~Component() = default;

			static void Destroy(Component* com)
			{
				if (!com)
					return;

				delete com;
			}

			ComponentType Type() const { return type; };
			Object* GameObject() const { return object; };
		private:
			ComponentType type;
			Object* object;
		};
	}
}

#endif