#include <stack>
#include "Scene.h"
#include "Tiny/Graphics/Scene/Camera.h"
#include "Tiny/Graphics/Mesh/Model.h"
#include "rapidjson/document.h"

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
						Object* target = Scene::Instance().FindObject("scene");
						cam->setSimpleMode(target);
					}
					else
					{
						cam->setFree3DMode();
					}
				}
			}
		}

		void CameraMove(const Input::KeyboardEvent& data)
		{
			float speed = 10.f;
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
				cam->distance = cam->distance <= 10.f ? 10.f : cam->distance - 10.f;
				cam->Rotate(0.f, 0.f);
			}

			if (data.button == Tiny::Input::MOUSEBTN::MOUSE_MIDDLE_BTN_SCROLL_UP)
			{
				comCamera* cam = Scene::Instance().GetMainCamera();
				cam->distance = cam->distance >= 1000.f ? 1000.f : cam->distance + 10.f;
				cam->Rotate(0.f, 0.f);
			}
		}

		void Scene::Load()
		{
			std::string basedir = Tiny::FileSystem::GetExePath();
			std::string cfgpath = basedir + "content\\Configs\\scene.json";

			rapidjson::Document cfg;
			std::string data = FileSystem::ReadChar(cfgpath);

			if (cfg.Parse(data.c_str()).HasParseError()) {
				Service::Log().E("scene.json parse error!");
				rapidjson::ParseErrorCode code = cfg.GetParseError();
				return;
			}

			for (auto& member : cfg.GetObject())
			{
				std::string modelname = member.name.GetString();
				auto& subcfg = member.value.GetObject();

				std::string respath = basedir;
				auto& rit = subcfg.FindMember("respath");
				if (rit != subcfg.MemberEnd())
				{
					respath += rit->value.GetString();
				}

				std::string vpath = basedir;
				auto& vit = subcfg.FindMember("vpath");
				if (vit != subcfg.MemberEnd())
				{
					vpath += vit->value.GetString();
				}
				
				std::string fpath = basedir;
				auto& fit = subcfg.FindMember("fpath");
				if (fit != subcfg.MemberEnd())
				{
					fpath += fit->value.GetString();
				}

				Math::Vector3f pos;
				auto& posit = subcfg.FindMember("position");
				for (unsigned int i = 0; i < posit->value.Size(); i++)
				{
					pos[i] = posit->value[i].GetFloat();
				}

				Math::Vector3f rot;
				auto& rotit = subcfg.FindMember("rotation");
				for (unsigned int i = 0; i < rotit->value.Size(); i++)
				{
					rot[i] = rotit->value[i].GetFloat();
				}

				Math::Vector3f scale;
				auto& scaleit = subcfg.FindMember("scale");
				for (unsigned int i = 0; i < scaleit->value.Size(); i++)
				{
					scale[i] = scaleit->value[i].GetFloat();
				}

				bool bPlayAnim = false;
				auto& bplayit = subcfg.FindMember("bPlayAnim");
				bPlayAnim = bplayit->value.GetBool();

				std::shared_ptr<Tiny::Graphics::Shader> shader = Tiny::ResourceLoader::Instance().LoadShader(vpath, fpath);
				Tiny::Graphics::Model* model = Tiny::Graphics::Model::New(modelname, respath, shader);
				model->Load();

				Object* obj = Tiny::Graphics::Scene::Instance().FindObject(modelname);
				obj->Transform().setPosition(pos);
				obj->Transform().setEulerAngles(rot);
				obj->Transform().setScale(scale);

				if (bPlayAnim)
					obj->PlayAnim(0, Tiny::Graphics::comSkinedMesh::AnimMode::LOOP);
			}
		}
	}
}
