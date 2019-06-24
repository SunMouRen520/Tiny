#ifndef _TINY_SKINEDMESH_H
#define _TINY_SKINEDMESH_H

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include "Tiny/Graphics/Mesh/Mesh.h"
#include <map>

namespace Tiny {
	namespace Graphics {
		class comSkinedMesh :public Component
		{
			friend class Object;
		public:
			static const int num_bones = 4;
			const int no_anim = -1;

			struct BoneInfo {
				Math::Matrix4f BoneOffset;
				Math::Matrix4f FinalTrans;
			};

			struct VertexBoneData {
				Math::Vector4i IDs;
				Math::Vector4f Weights;

				void AddBoneData(int id, float weight);
			};

			enum class AnimMode {
				LOOP,
				SINGLE,
			};

		public:
			static ComponentType TYPE;
			virtual ~comSkinedMesh();
			comSkinedMesh(const comSkinedMesh&) = delete;
			comSkinedMesh& operator=(const comSkinedMesh&) = delete;
			void setMaterial(std::shared_ptr<Material> mat) { material = mat; }
			std::shared_ptr<Material> getMaterial() { return material; }
			void Draw();
		public:
			unsigned int getVAO() { return VAO; }
			unsigned int getPolysNum() { return polys.size(); }
			void InitMesh(const aiMesh*, const aiScene*);
			void InitBone(const aiMesh*);
			void BoneTransform(std::vector<Math::Matrix4f>&);
			Math::Matrix4f BoneTransformMatrix(float tick, const aiNode* node);
			Math::Matrix4f NodeTransformMatrix(float tick, const aiNode* node);
			const aiNodeAnim* FindNodeAnim(const aiAnimation* anim, std::string nodeName);
			void CalcInterpolatedScaling(aiVector3D& out, float tick, const aiNodeAnim* nodeAnim);
			void CalcInterpolatedRotation(aiQuaternion& out, float tick, const aiNodeAnim* nodeAnim);
			void CalcInterpolatedPosition(aiVector3D& out, float tick, const aiNodeAnim* nodeAnim);
			void PlayAnim(std::string, AnimMode);
			void PlayAnim(std::size_t, AnimMode);
		private:
			static comSkinedMesh* New(Object*);
			comSkinedMesh(Object* obj) :Component(ComponentType::SkinedMesh, obj) {}
			//material
			std::shared_ptr<Material> material;
			//mesh data
			std::vector<Vertex> vertexs;
			std::vector<VertexBoneData> bones;
			std::vector<Poly> polys;
			//bone data
			std::map<std::string, int> boneMap;
			std::vector<BoneInfo> boneInfo;
			Math::Matrix4f globalInverseTrans;

			const aiScene* scene;
		private:
			float startTime;
			int activeAnim = no_anim;
			AnimMode mode;
		private:
			//render data
			unsigned int VAO = 0;
			unsigned int VVBO = 0;
			unsigned int BVBO = 0;
			unsigned int EBO = 0;
		};
	}
}

#endif