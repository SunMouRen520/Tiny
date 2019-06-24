#include <stack>

#include "Object.h"
#include "Tiny/Core/Service.h"
#include "Tiny/Graphics/Scene/Scene.h"


namespace Tiny {
	namespace Graphics {

		Object* Object::New(std::string name)
		{
			Object* obj = new Object(name);
			Scene::Instance().insertObject(obj);
			obj->scene = &Scene::Instance();
			return obj;
		}

		bool Object::Destroy(Object* object)
		{
			if (!object)
				return false;
			//remove from parent
			if (object->parent)
				object->parent->RemoveChild(object);
			//remove form scene
			if (object->scene)
			{
				object->scene->removeObject(object);
			}
			//destroy child recursively
			object->Destroy();
		}

		Object* Object::Root()
		{
			return parent ? parent->Root() : this;
		}

		bool Object::AddChild(Object* child)
		{
			if (!child)
			{
				Service::Log().W("child is null");
				return false;
			}
			if (this == child)
			{
				Service::Log().W("Object can not attach to self");
				return false;
			}
			if (children.find(child->GetInstanceID()) != children.end())
			{
				Service::Log().W("there has a instanceid the same as object in the parent's children");
				return false;
			}
			//self and child at the same tree, should avoid child is self's parent node
			if (this->Root() == child->Root())
			{
				Object* p = parent;
				while (p)
				{
					if (p == child)
					{
						Service::Log().W("parent node can not attach to child node");
						return false;
					}
					p = p->parent;
				}
			}
			//if child object has parent, remove from the parent
			if (child->parent)
			{
				child->parent->RemoveChild(child);
				child->parent = nullptr;
			}
			//if child object has not parent, it should remove from scene
			if (child->scene)
			{
				child->scene->removeObject(child);
				child->scene = nullptr;
			}

			children[child->GetInstanceID()] = child;
			child->parent = this;
			child->Transform().SetParent(&transform);

			return true;
		}
		//only called by addchild and destroy
		void Object::RemoveChild(Object* child)
		{
			if (children.find(child->GetInstanceID()) != children.end())
				children.erase(child->GetInstanceID());
		}

		Object* Object::FindChild(std::string name)
		{
			std::stack<Object*> objStack;
			objStack.push(this);

			while (!objStack.empty())
			{
				Object* obj = objStack.top();
				if (obj->Name() == name)
					return obj;

				objStack.pop();
				//push children
				for (auto item : obj->children)
				{
					objStack.push(item.second);
				}
			}

			return nullptr;
		}

		bool Object::AttachToParent(Object* parentptr)
		{
			if (!parentptr)
			{
				Service::Log().W("Object attach to parent failed, parent is null");
				return false;
			}
			
			return parentptr->AddChild(this);
		}

		void Object::RemoveAllComponents()
		{
			for (auto b = coms.begin(); b != coms.end(); b++)
			{
				Component::Destroy(*b);
			}

			coms.clear();
		}

		void Object::Destroy()
		{
			for (std::pair<std::size_t, Object*> child : children)
			{
				if (child.second)
					child.second->Destroy();
			}
			//remove all components
			RemoveAllComponents();
			delete this;
		}

		void Object::PlayAnim(std::string anim, comSkinedMesh::AnimMode mode)
		{
			std::stack<Object*> objStack;
			objStack.push(this);

			while (!objStack.empty())
			{
				Object* obj = objStack.top();
				comSkinedMesh* mesh = obj->GetComponent<comSkinedMesh>();
				if(mesh)
					mesh->PlayAnim(anim, mode);

				objStack.pop();
				//push children
				for (auto item : obj->children)
				{
					objStack.push(item.second);
				}
			}
		}

		void Object::PlayAnim(std::size_t anim, comSkinedMesh::AnimMode mode)
		{
			std::stack<Object*> objStack;
			objStack.push(this);

			while (!objStack.empty())
			{
				Object* obj = objStack.top();
				comSkinedMesh* mesh = obj->GetComponent<comSkinedMesh>();
				if(mesh)
					mesh->PlayAnim(anim, mode);

				objStack.pop();
				//push children
				for (auto item : obj->children)
				{
					objStack.push(item.second);
				}
			}
		}
	}
}