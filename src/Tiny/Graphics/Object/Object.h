#ifndef _TINY_OBJECT_H
#define _TINY_OBJECT_H

#include <vector>
#include <map>
#include <memory>

#include "Transform.h"
#include "Tiny/Graphics/Mesh/SkinedMesh.h"
#include "Tiny/Graphics/UniqueID.h"

namespace Tiny {
	namespace Graphics {
		const int _maxObject = 1000;
		using Transformf = Transform<float>;
		class Scene;
		class Object
		{
		public:
			Object & operator=(const Object&) = delete;
			Object(const Object&) = delete;
			//obj name must be unique so that can be found
			static Object* New(std::string name = "");
			static bool Destroy(Object*);
		private:
			//Avoid object creation on the stack
			Object(std::string str) :name(str) {}
		public:
			//Get instanceid
			std::size_t GetInstanceID() { return uniqueID(); }
			//Get name
			std::string Name() const { return name; }
			//Get parent
			Object* Parent() const { return parent; }
			//Get scene
			Scene* getScene() const { return scene; }
			//Get root
			Object* Root();
			//Get children
			std::map<std::size_t, Object*> Children() { return children; }
			//Attach to parent node
			bool AttachToParent(Object*);
			//Add child
			bool AddChild(Object*);
			//Find child
			Object* FindChild(std::string name);
			//play anim
			void PlayAnim(std::string, comSkinedMesh::AnimMode);
			void PlayAnim(std::size_t, comSkinedMesh::AnimMode);
		private:
			//Remove child, only called by AddChild and Destroy
			void RemoveChild(Object*);
			void Destroy();
		private:
			//Instance id
			UniqueID<Object, _maxObject> uniqueID;
			//Object name
			std::string name;
			//Object attri, bitwise
			std::size_t attri = 0;
			//Object layer
			std::size_t layer = 0;
			//Parent
			Object* parent = nullptr;
			//Scene
			Scene* scene = nullptr;
			//Children, find by instanceid
			std::map<std::size_t, Object*> children;
		public:
			//Only transform component return refrence
			Transformf & Transform() { return transform; }
			//Add component to the game object,the template must be explicit called
			template<typename T> T* AddComponent();
			//Return the component of Type type if the object has one attached, null if it doesn't
			//the template must be explicit called
			template<typename T> T* GetComponent();
			//Remove component atttached to object, the template must be explicit called
			template<typename T> bool RemoveComponent();
			//Remove all components
			void RemoveAllComponents();
		private:
			//Component
			Transformf transform;
			std::vector<Component*> coms;
		};

		template<typename T> T* Object::AddComponent()
		{
			T* com = GetComponent<T>();
			if (com)
				RemoveComponent<T>();

			com = T::New(this);
			coms.push_back(com);
			return com;
		}

		template<typename T> bool Object::RemoveComponent()
		{
			for (auto b = coms.begin(); b != coms.end(); b++)
			{
				if (T::TYPE == (*b)->Type())
				{
					Component::Destroy(*b);
					coms.erase(b);
					break;
				}
			}
			
			return true;
		}

		template<typename T> T* Object::GetComponent()
		{
			for (Component* com : coms)
			{
				if (T::TYPE == com->Type())
					return dynamic_cast<T*>(com);
			}

			return nullptr;
		}
	}
}



#endif