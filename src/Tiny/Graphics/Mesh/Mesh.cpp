#include "Mesh.h"
#include "Tiny/Core/Service.h"

namespace Tiny {
	namespace Graphics {
		ComponentType comMesh::TYPE = ComponentType::Mesh;

		comMesh::~comMesh()
		{
			if (VAO != 0)
				glDeleteVertexArrays(1, &VAO);
			if (VBO != 0)
				glDeleteBuffers(1, &VBO);
			if (EBO != 0)
				glDeleteBuffers(1, &EBO);
		}

		comMesh* comMesh::New(Object* obj)
		{
			if (!obj)
			{
				Service::Log().W("Mesh creation failed, obj null");
				return nullptr;
			}

			return new comMesh(obj);
		}

		void comMesh::initMesh(aiMesh* mesh)
		{
			for (unsigned int i = 0; i < mesh->mNumVertices; i++)
			{
				Vertex vertex;
				vertex.v = Math::Vector3f(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
				vertex.n = Math::Vector3f(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
				if (mesh->mTextureCoords[0])
				{
					vertex.t = Math::Vector2f(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
				}
				else
				{
					vertex.t = Math::Vector2f(0.f, 0.f);
				}

				vertexs.push_back(vertex);
			}

			for (unsigned int i = 0; i < mesh->mNumFaces; i++)
			{
				Poly poly;
				aiFace face = mesh->mFaces[i];
				poly.indices = Math::Vector3i(face.mIndices[0], face.mIndices[1], face.mIndices[2]);
				polys.push_back(poly);
			}

			glGenVertexArrays(1, &VAO);
			glGenBuffers(1, &VBO);
			glGenBuffers(1, &EBO);

			glBindVertexArray(VAO);
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, vertexs.size() * sizeof(Vertex), &vertexs[0], GL_STATIC_DRAW);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, polys.size() * sizeof(Poly), &polys[0], GL_STATIC_DRAW);
		
			//vertex attri
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(Vertex), (void*)0);

			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 3, GL_FLOAT, false, sizeof(Vertex), (void*)offsetof(Vertex, n));

			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, 2, GL_FLOAT, false, sizeof(Vertex), (void*)offsetof(Vertex, t));

			glBindVertexArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}

		void comMesh::Draw()
		{
			if (material)
			{
				std::shared_ptr<Shader> shader = material->getShader();
				shader->use();

				material->Render();
			}
		}
	}
}