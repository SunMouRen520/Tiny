#include <stack>
#include "Scene.h"
#include "Tiny/Graphics/Scene/Camera.h"
#include "Tiny/Graphics/Mesh/SkinedMesh.h"

namespace Tiny {
	namespace Graphics {
		Scene& Scene::Instance()
		{
			static Scene instance;
			return instance;
		}

		void Scene::insertObject(Object* obj)
		{
			if (!obj)
				return;
			objMap[obj->GetInstanceID()] = obj;
		}

		void Scene::removeObject(Object* obj)
		{
			if (!obj)
				return;
			objMap.erase(obj->GetInstanceID());
		}

		Object* Scene::FindObject(const std::string& name)
		{
			for (auto item : objMap)
			{
				if (item.second->Name() == name)
				{
					return item.second;
				}
			}

			return nullptr;
		}

		void Scene::CreateMainCamera()
		{
			Object* camera = Object::New("MainCamera");
			mainCam = camera->AddComponent<comCamera>();
		}

		comCamera* Scene::GetMainCamera()
		{
			return mainCam;
		}
		//test implementation
		void Scene::Draw()
		{
			Scene& instance = Scene::Instance();
			
			std::stack<Object*> objStack;
			for (auto item : instance.objMap)
			{
				objStack.push(item.second);
			}

			while (!objStack.empty())
			{
				Object* obj = objStack.top();

				comMesh* mesh = obj->GetComponent<comMesh>();
				if (mesh)
					mesh->Draw();

				comSkinedMesh* skinmesh = obj->GetComponent<comSkinedMesh>();
				if (skinmesh)
					skinmesh->Draw();

				objStack.pop();
				//push children
				for (auto item : obj->Children())
				{
					objStack.push(item.second);
				}
			}
		}

		void ProcessKeyBoard(const Input::KeyboardEvent& data)
		{
			CameraMove(data);

			if (data.pressed)
			{
				comCamera* cam = Scene::Instance().GetMainCamera();
				if (data.key == Tiny::Input::KEYBOARD::F1)
				{
					if (cam->type() == comCamera::CAM_TYPE::FREE_3D)
					{
						Object* target = Scene::Instance().FindObject("TestModel");
						cam->setSimpleMode(target);
					}
					else
					{
						cam->setFree3DMode();
					}
				}
				else if (data.key == Tiny::Input::KEYBOARD::F2)
				{
					//Object* model = Scene::Instance().FindObject("SkinedModel");
					//model->PlayAnim(0, comSkinedMesh::AnimMode::LOOP);
				}
			}
		}

		void CameraMove(const Input::KeyboardEvent& data)
		{
			float speed = 1.f;
			if (data.pressed)
			{
				comCamera* cam = Scene::Instance().GetMainCamera();
				if (data.key == Tiny::Input::KEYBOARD::KEY_W)
					cam->Translate(0, 0, speed);
				else if (data.key == Tiny::Input::KEYBOARD::KEY_S)
					cam->Translate(0, 0, -speed);
				else if (data.key == Tiny::Input::KEYBOARD::KEY_A)
					cam->Translate(-speed, 0, 0);
				else if (data.key == Tiny::Input::KEYBOARD::KEY_D)
					cam->Translate(speed, 0, 0);
				else if (data.key == Tiny::Input::KEYBOARD::KEY_E)
					cam->Translate(0, speed, 0);
				else if (data.key == Tiny::Input::KEYBOARD::KEY_Q)
					cam->Translate(0, -speed, 0);
			}
		}

		void CameraRotate(const Input::MouseBtnEvent& data)
		{
			if (data.holding && (data.button == Tiny::Input::MOUSEBTN::MOUSE_LEFT_BTN))
			{
				comCamera* cam = Scene::Instance().GetMainCamera();
				cam->Rotate(data.deltaPosition.X(), data.deltaPosition.Y());
			}
			
			if (data.button == Tiny::Input::MOUSEBTN::MOUSE_MIDDLE_BTN_SCROLL_DOWN)
			{
				comCamera* cam = Scene::Instance().GetMainCamera();
				cam->distance = cam->distance <= 1.f ? 1.f : cam->distance - 1.f;
				cam->Rotate(0.f, 0.f);
			}

			if (data.button == Tiny::Input::MOUSEBTN::MOUSE_MIDDLE_BTN_SCROLL_UP)
			{
				comCamera* cam = Scene::Instance().GetMainCamera();
				cam->distance = cam->distance >= 20.f ? 20.f : cam->distance + 1.f;
				cam->Rotate(0.f, 0.f);
			}
		}
	}
}
