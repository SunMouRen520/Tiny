#ifndef _TINY_OBJECT_H
#define _TINY_OBJECT_H

#include <vector>
#include <map>
#include <memory>

#include "Transform.h"
#include "../Mesh/Mesh.h"
#include "../Scene/Camera.h"
#include "../Scene/Light.h"

namespace Tiny {
	namespace Graphics {
		using Transformf = Transform<float>;
		class Object
		{
		public:
			Object & operator=(const Object&) = delete;
			Object(const Object&) = delete;

			//static Object* New();
			static Object* New(std::string name = "");
			static bool Destroy(Object*);
		private:
			//Avoid object creation on the stack
			Object(std::string str) { instanceid = uniqueID++; name = str; }
		public:
			//Get instanceid
			std::size_t GetInstanceID() { return instanceid; }
			//Get parent
			Object* Parent() { return parent; }
			//Get root
			Object* Root();
			//Get children
			std::map<std::size_t, Object*> Children() { return children; }
			//Attach to parent node
			bool AttachToParent(Object*);
			//Add child
			bool AddChild(Object*);
		private:
			//Remove child, only called by AddChild and Destroy
			void RemoveChild(Object*);
			void Destroy();
		private:
			static std::size_t uniqueID;
			//Instance id
			std::size_t instanceid;
			//Object name
			std::string name;
			//Object attri, bitwise
			std::size_t attri = 0;
			//Object layer
			std::size_t layer = 0;
			//Parent
			Object* parent = nullptr;
			//Children, find by instanceid
			std::map<std::size_t, Object*> children;
		public:
			//Only transform component return refrence
			Transformf & Transform() { return transform; }
			//Add component to the game object,the template must be explicit called
			template<typename T> bool AddComponent();
			//Return the component of Type type if the object has one attached, null if it doesn't
			//the template must be explicit called
			template<typename T> T* GetComponent();
			//Remove component atttached to object, the template must be explicit called
			template<typename T> bool RemoveComponent();
		private:
			//Component
			Transformf transform;
			comMesh* mesh = nullptr;
			comCamera* camera = nullptr;
			comLight* light = nullptr;
		};


		template<typename T> bool Object::AddComponent()
		{
			if (T::TYPE == ComponentType::Mesh)
			{
				if (mesh)
					RemoveComponent<T>();
				mesh = comMesh::New(this);
			}
			else if (T::TYPE == ComponentType::Camera)
			{
				if (camera)
					RemoveComponent<T>();
				camera = comCamera::New(this);
			}
			else if (T::TYPE == ComponentType::Light)
			{
				if (light)
					RemoveComponent<T>();
				light = comLight::New(this);
			}
			else
				return false;
			return true;
		}

		template<typename T> bool Object::RemoveComponent()
		{
			if (T::TYPE == ComponentType::Mesh)
				comMesh::Destroy(mesh);
			else if (T::TYPE == ComponentType::Camera)
				comCamera::Destroy(camera);
			else if (T::TYPE == ComponentType::Light)
				comLight::Destroy(light);
			else
				return false;
			return true;
		}

		template<typename T> T* Object::GetComponent()
		{
			if (T::TYPE == ComponentType::Mesh)
				return mesh ? reinterpret_cast<T*>(mesh) : nullptr;
			else if (T::TYPE == ComponentType::Camera)
				return camera ? reinterpret_cast<T*>(camera) : nullptr;
			else if (T::TYPE == ComponentType::Light)
				return light ? reinterpret_cast<T*>(light) : nullptr;

			return nullptr;
		}
	}
}



#endif