#ifndef _TINY_MODEL_H
#define _TINY_MODEL_H

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include "Mesh.h"
#include "SkinedMesh.h"
#include "Tiny/Graphics/Object/Object.h"

namespace Tiny {
	namespace Graphics {
		class Model
		{
		public:
			static Model* New(std::string strname, std::string strpath, std::shared_ptr<Shader> s) { return new Model(strname, strpath, s); }
			void Load();
		private:
			Model(std::string strname, std::string strpath, std::shared_ptr<Shader> s) :name(strname), path(strpath), shader(s) {};
			void ProcessMesh(const aiScene* scene, Object* parent);
			std::string name;
			std::string path;
			std::shared_ptr<Shader> shader;
			Object* model;

			Assimp::Importer importer;
		};
	}
}


#endif