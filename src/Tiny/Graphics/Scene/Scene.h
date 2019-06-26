#ifndef _TINY_SCENE_H
#define _TINY_SCENE_H

#include "Tiny/Graphics/Object/Object.h"
#include "Tiny/Graphics/Scene/Camera.h"
#include "Tiny/Input/InputEvent.h"

namespace Tiny {
	namespace Graphics {
		class Scene
		{
		public:
			static Scene& Instance();
			void CreateMainCamera();
			comCamera* GetMainCamera();
			void Draw();
			void insertObject(Object*);
			void removeObject(Object*);
			Object* FindObject(const std::string& name);
			std::map<std::size_t, Object*> ObjMap() { return objMap; }
			void Load();
		private:
			comCamera* mainCam;
			std::map<std::size_t, Object*> objMap;
		};

		void ProcessKeyBoard(const Input::KeyboardEvent& data);
		void CameraMove(const Input::KeyboardEvent& data);
		void CameraRotate(const Input::MouseBtnEvent& data);
	}
}


#endif