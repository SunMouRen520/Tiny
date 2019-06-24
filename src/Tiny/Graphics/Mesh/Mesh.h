#ifndef _TINY_MESH_H
#define _TINY_MESH_H

#include "Tiny/Graphics/Object/Component.h"
#include "Tiny/Graphics/Shader/Material.h"

namespace Tiny {
	namespace Graphics {
		typedef struct
		{
			Math::Vector3f v; //position
			Math::Vector3f n; //normal
			Math::Vector2f t; //texture coordinate
		}Vertex, *Vertex_Ptr;

		typedef struct
		{
			Math::Vector3i indices;//vertex index
		}Poly, *Poly_Ptr;

		class comMesh :public Component
		{
			friend class Object;
		public:
			static ComponentType TYPE;
			virtual ~comMesh();
			comMesh(const comMesh&) = delete;
			comMesh& operator=(const comMesh&) = delete;
			void initMesh(aiMesh*);
			unsigned int getVAO() { return VAO; }
			unsigned int getPolysNum() { return polys.size(); }
			void setMaterial(std::shared_ptr<Material> mat) { material = mat; }
			std::shared_ptr<Material> getMaterial() { return material; }
			void Draw();
		private:
			//only called by Object
			static comMesh* New(Object*);
			comMesh(Object* obj) :Component(ComponentType::Mesh, obj) {}
			//material
			std::shared_ptr<Material> material;
			//mesh data
			std::vector<Vertex> vertexs;
			std::vector<Poly> polys;
		private:
			//render data
			unsigned int VAO = 0;
			unsigned int VBO = 0;
			unsigned int EBO = 0;
		};
	}
}

#endif