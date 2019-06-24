#include "Material.h"
#include "Tiny/Graphics/Mesh/SkinedMesh.h"
#include "Tiny/Graphics/Object/Object.h"
#include "Tiny/Graphics/Scene/Scene.h"

namespace Tiny {
	namespace Graphics {
		void Material::initMat(aiMaterial* mat)
		{
			if (!mat)
				return;				
			
			std::vector<std::shared_ptr<Texture>> diffuse = loadMaterialTextures(mat, aiTextureType_DIFFUSE);
			textures.insert(textures.end(), diffuse.begin(), diffuse.end());
			std::vector<std::shared_ptr<Texture>> specular = loadMaterialTextures(mat, aiTextureType_SPECULAR);
			textures.insert(textures.end(), specular.begin(), specular.end());
		}

		std::vector<std::shared_ptr<Texture>> Material::loadMaterialTextures(aiMaterial* mat, aiTextureType type)
		{
			std::size_t index = respath.find_last_of("\\");
			std::string baseDir = respath.substr(0, index + 1);

			std::vector<std::shared_ptr<Texture>> textures;
			for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
			{
				aiString path;
				mat->GetTexture(type, i, &path);
				
				TextureType ttype;
				if (type == aiTextureType_DIFFUSE)
					ttype = TextureType::Diffuse;
				else if (type == aiTextureType_SPECULAR)
					ttype = TextureType::Specular;
				else
					ttype = TextureType::Unknown;
				std::shared_ptr<Texture> texture = Texture::Texture2D(baseDir + path.C_Str(), ttype);
				textures.push_back(texture);
			}

			return textures;
		}

		void Material::Render()
		{
			if (!mesh)
				return;

			Object* obj = mesh->GameObject();
			if (!obj)
				return;

			Math::Matrix4f model = obj->Transform().localToWorldMatrix();
			shader->setMat4("model", model);

			comCamera* cam = Scene::Instance().GetMainCamera();

			Math::Matrix4f view = cam->viewMatrix();
			Math::Matrix4f projection = cam->perspectMatrix();

			shader->setMat4("view", view);
			shader->setMat4("projection", projection);

			unsigned int VAO = 0;
			unsigned int polynum = 0;
			if (mesh->Type() == ComponentType::Mesh)
			{
				VAO = (dynamic_cast<comMesh*>(mesh))->getVAO();
				polynum = (dynamic_cast<comMesh*>(mesh))->getPolysNum();
			}
			else if (mesh->Type() == ComponentType::SkinedMesh)
			{
				VAO = (dynamic_cast<comSkinedMesh*>(mesh))->getVAO();
				polynum = (dynamic_cast<comSkinedMesh*>(mesh))->getPolysNum();
			}

			unsigned int diffuseNr = 1;
			unsigned int specularNr = 1;
			for (unsigned int i = 0; i < textures.size(); i++)
			{
				glActiveTexture(GL_TEXTURE0 + i);
				
				std::string number;
				std::string name;
				TextureType type = textures[i]->_type;
				if (type == TextureType::Diffuse)
					name = "texture_diffuse" + std::to_string(diffuseNr++);
				else if (type == TextureType::Specular)
					name = "texture_specular" + std::to_string(specularNr++);

				shader->setInt(name, i);
				glBindTexture(GL_TEXTURE_2D, textures[i]->ID);
			}

			glBindVertexArray(VAO);
			glDrawElements(GL_TRIANGLES, polynum * 3, GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);

			glActiveTexture(GL_TEXTURE0);
		}
	}
}