#ifndef _TINY_MATERIAL_H
#define _TINY_MATERIAL_H

#include "Shader.h"
#include "Tiny/Graphics/Scene/Camera.h"
#include "Tiny/Graphics/Texture/TextureData.h"
#include "Tiny/Core/Resource/ResourceManager.h"
#include "assimp/scene.h"

namespace Tiny {
	namespace Graphics {
		class comMesh;
		class Material
		{
		public:
			Material(std::shared_ptr<Shader> s,std::string path, Component* m = nullptr) :
				shader(s), respath(path), mesh(m)  {}
			void initMat(aiMaterial*);
			std::vector<std::shared_ptr<Texture>> loadMaterialTextures(aiMaterial*, aiTextureType);
			std::shared_ptr<Shader> getShader() { return shader; }
			virtual void Render();
			virtual ~Material() = default;
		private:
			//mesh data
			Component* mesh;
			//shader program
			std::shared_ptr<Shader> shader;
			//model res path
			std::string respath;
			//ambient and diffuse share the diffuseTex
			std::vector<std::shared_ptr<Texture>> textures;
		};
	}
}


#endif