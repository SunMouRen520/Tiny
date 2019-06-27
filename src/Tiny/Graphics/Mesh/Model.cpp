#include "Model.h"
#include "Tiny/Graphics/Scene/Scene.h"
#include "Tiny/Core/Service.h"

namespace Tiny {
	namespace Graphics {
		void Model::Load()
		{
			const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_MakeLeftHanded | aiProcess_FlipUVs | aiProcess_GenNormals | aiProcess_JoinIdenticalVertices);
			if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
			{
				Service::Log().W("load model failed path:{}", path);
				return;
			}

			model = Object::New(name);
			ProcessMesh(scene, model);
		}

		void Model::ProcessMesh(const aiScene* scene, Object* parent)
		{
			for (unsigned int i = 0; i < scene->mNumMeshes; i++)
			{
				aiMesh* aimesh = scene->mMeshes[i];
				//create object
				Object* obj = Object::New(aimesh->mName.C_Str());
				obj->AttachToParent(parent);

				if (scene->mNumAnimations == 0)
				{
					//add component
					comMesh* mesh = obj->AddComponent<comMesh>();
					mesh->initMesh(aimesh);
					//attach material
					aiMaterial* material = scene->mMaterials[aimesh->mMaterialIndex];
					std::shared_ptr<Material> mat = std::make_shared<Material>(shader, path, mesh);
					mat->initMat(material);
					mesh->setMaterial(mat);
				}
				else
				{
					comSkinedMesh* mesh = obj->AddComponent<comSkinedMesh>();
					mesh->InitMesh(aimesh, scene);

					aiMaterial* material = scene->mMaterials[aimesh->mMaterialIndex];
					std::shared_ptr<Material> mat = std::make_shared<Material>(shader, path, mesh);
					mat->initMat(material);
					mesh->setMaterial(mat);
				}
			}
		}
	}
}