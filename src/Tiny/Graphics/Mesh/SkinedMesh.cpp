#include "SkinedMesh.h"
#include "Tiny/Core/Service.h"

namespace Tiny {
	namespace Graphics {
		ComponentType comSkinedMesh::TYPE = ComponentType::SkinedMesh;

		void comSkinedMesh::VertexBoneData::AddBoneData(int id, float weight)
		{
			for (int i = 0; i < comSkinedMesh::num_bones; i++)
			{
				if (Weights[i] == 0.f)
				{
					IDs[i] = id;
					Weights[i] = weight;
					return;
				}
			}
		}

		comSkinedMesh::~comSkinedMesh()
		{
			if (VAO != 0)
				glDeleteVertexArrays(1, &VAO);
			if (VVBO != 0)
				glDeleteBuffers(1, &VVBO);
			if (BVBO != 0)
				glDeleteBuffers(1, &BVBO);
			if (EBO != 0)
				glDeleteBuffers(1, &EBO);
		}

		comSkinedMesh* comSkinedMesh::New(Object* obj)
		{
			if (!obj)
			{
				Service::Log().W("Mesh creation failed, obj null");
				return nullptr;
			}

			return new comSkinedMesh(obj);
		}

		void comSkinedMesh::InitMesh(const aiMesh* mesh, const aiScene* s)
		{
			scene = s;

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

			InitBone(mesh);

			glGenVertexArrays(1, &VAO);
			glGenBuffers(1, &VVBO);
			glGenBuffers(1, &BVBO);
			glGenBuffers(1, &EBO);

			glBindVertexArray(VAO);
			glBindBuffer(GL_ARRAY_BUFFER, VVBO);
			glBufferData(GL_ARRAY_BUFFER, vertexs.size() * sizeof(Vertex), &vertexs[0], GL_STATIC_DRAW);

			//vertex attri
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(Vertex), (void*)0);

			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 3, GL_FLOAT, false, sizeof(Vertex), (void*)offsetof(Vertex, n));

			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, 2, GL_FLOAT, false, sizeof(Vertex), (void*)offsetof(Vertex, t));

			glBindBuffer(GL_ARRAY_BUFFER, BVBO);
			glBufferData(GL_ARRAY_BUFFER, bones.size() * sizeof(VertexBoneData), &bones[0], GL_STATIC_DRAW);
				
			glEnableVertexAttribArray(3);
			glVertexAttribIPointer(3, 4, GL_INT, sizeof(VertexBoneData), (void*)0);
			glEnableVertexAttribArray(4);
			glVertexAttribIPointer(4, 4, GL_INT, sizeof(VertexBoneData), (void*)16);
			glEnableVertexAttribArray(5);
			glVertexAttribIPointer(5, 4, GL_INT, sizeof(VertexBoneData), (void*)32);
			glEnableVertexAttribArray(6);
			glVertexAttribIPointer(6, 4, GL_INT, sizeof(VertexBoneData), (void*)48);

			glEnableVertexAttribArray(7);
			glVertexAttribPointer(7, 4, GL_FLOAT, false, sizeof(VertexBoneData), (void*)offsetof(VertexBoneData, Weights));
			glEnableVertexAttribArray(8);
			glVertexAttribPointer(8, 4, GL_FLOAT, false, sizeof(VertexBoneData), (void*)(offsetof(VertexBoneData, Weights) + 16));
			glEnableVertexAttribArray(9);
			glVertexAttribPointer(9, 4, GL_FLOAT, false, sizeof(VertexBoneData), (void*)(offsetof(VertexBoneData, Weights) + 32));
			glEnableVertexAttribArray(10);
			glVertexAttribPointer(10, 4, GL_FLOAT, false, sizeof(VertexBoneData), (void*)(offsetof(VertexBoneData, Weights) + 48));

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, polys.size() * sizeof(Poly), &polys[0], GL_STATIC_DRAW);

			glBindVertexArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}

		void comSkinedMesh::InitBone(const aiMesh* mesh)
		{
			bones.resize(mesh->mNumVertices);

			int numBones = 0;
			for (unsigned int i = 0; i < mesh->mNumBones; i++)
			{
				unsigned int boneIndex = 0;
				std::string boneName(mesh->mBones[i]->mName.C_Str());

				if (boneMap.find(boneName) == boneMap.end())
				{
					boneIndex = numBones;
					numBones++;
					BoneInfo bi;
					bi.BoneOffset = Math::RectangularMatrix<4,4,float>::From(&mesh->mBones[i]->mOffsetMatrix.a1).Transpose();
					boneInfo.push_back(bi);
					boneMap[boneName] = boneIndex;
				}
				else
				{
					boneIndex = boneMap[boneName];
				}

				for (unsigned int j = 0; j < mesh->mBones[i]->mNumWeights; j++)
				{
					unsigned int vertexId = mesh->mBones[i]->mWeights[j].mVertexId;
					float weight = mesh->mBones[i]->mWeights[j].mWeight;
					bones[vertexId].AddBoneData(boneIndex, weight);
				}
			}
		}

		void comSkinedMesh::BoneTransform(std::vector<Math::Matrix4f>& Transforms)
		{
			if (activeAnim == no_anim)
			{
				Transforms.resize(boneInfo.size());
				for (unsigned int i = 0; i < boneInfo.size(); i++)
				{
					Transforms[i] = boneInfo[i].FinalTrans;
				}
				return;
			}

			float curTime = Service::Time().GetTimeSinceLaunch(TimePrecision::MILLISEC) / 1000.0;
			float deltaTime = curTime - startTime;

			float ticksPerSec = (float)(scene->mAnimations[activeAnim]->mTicksPerSecond != 0.f ? scene->mAnimations[activeAnim]->mTicksPerSecond : 25.f);
			float timeTicks = deltaTime * ticksPerSec;
			float animTicks = (float)(scene->mAnimations[activeAnim]->mDuration);
			
			if (mode == AnimMode::SINGLE && timeTicks > animTicks)
			{
				activeAnim = no_anim;
				return;
			}
			else if (mode == AnimMode::LOOP)
			{
				timeTicks = fmod(timeTicks, animTicks);
			}
			
			for (std::map<std::string, int>::iterator it = boneMap.begin(); it != boneMap.end(); it++)
			{
				std::string boneName = it->first;
				int boneIndex = it->second;

				aiNode* boneNode = scene->mRootNode->FindNode(boneName.c_str());
				if (boneNode)
				{
					Math::Matrix4f boneTransform = BoneTransformMatrix(timeTicks, boneNode);
					boneInfo[boneIndex].FinalTrans = boneInfo[boneIndex].BoneOffset * boneTransform;
				}
			}

			Transforms.resize(boneInfo.size());
			for (unsigned int i = 0; i < boneInfo.size(); i++)
			{
				Transforms[i] = boneInfo[i].FinalTrans;
			}
		}

		Math::Matrix4f comSkinedMesh::BoneTransformMatrix(float tick, const aiNode* node)
		{
			Math::Matrix4f resMat;

			while (node != scene->mRootNode)
			{
				resMat *= NodeTransformMatrix(tick, node);
				node = node->mParent;
			}

			return resMat;
		}

		Math::Matrix4f comSkinedMesh::NodeTransformMatrix(float tick, const aiNode* node)
		{
			std::string nodeName(node->mName.C_Str());

			const aiAnimation* anim = scene->mAnimations[activeAnim];

			Math::Matrix4f nodeTransformation = Math::RectangularMatrix<4, 4, float>::From(&node->mTransformation.a1);
			
			const aiNodeAnim* nodeAnim = FindNodeAnim(anim, nodeName);
			
			if (nodeAnim)
			{
				aiVector3D scaling;
				CalcInterpolatedScaling(scaling, tick, nodeAnim);
				Math::Matrix4f scalingMat = Math::Matrix4f::Scale({ scaling.x, scaling.y, scaling.z });

				aiQuaternion rotation;
				CalcInterpolatedRotation(rotation, tick, nodeAnim);
				aiMatrix4x4 rotMat = aiMatrix4x4(rotation.GetMatrix());
				Math::Matrix4f rotationMat = Math::RectangularMatrix<4, 4, float>::From(&rotMat.a1).Transpose();

				aiVector3D position;
				CalcInterpolatedPosition(position, tick, nodeAnim);
				Math::Matrix4f translationMat = Math::Matrix4f::Translation({ position.x, position.y, position.z });
			
				nodeTransformation = scalingMat * rotationMat * translationMat;
			}

			return nodeTransformation;
		}

		const aiNodeAnim* comSkinedMesh::FindNodeAnim(const aiAnimation* anim, std::string nodeName)
		{
			for (unsigned int i = 0; i < anim->mNumChannels; i++)
			{
				const aiNodeAnim* nodeAnim = anim->mChannels[i];
				
				if (nodeAnim->mNodeName.C_Str() == nodeName)
				{
					return nodeAnim;
				}
			}
			return nullptr;
		}

		void comSkinedMesh::CalcInterpolatedScaling(aiVector3D& out, float tick, const aiNodeAnim* nodeAnim)
		{
			if (nodeAnim->mNumScalingKeys == 1)
			{
				out = nodeAnim->mScalingKeys[0].mValue;
				return;
			}

			unsigned int scaleIndex = 0;

			for (unsigned int i = 0; i < nodeAnim->mNumScalingKeys - 1; i++)
			{
				if (tick < (float)nodeAnim->mScalingKeys[i + 1].mTime)
				{
					scaleIndex = i;
					break;
				}
			}

			unsigned int nextScaleIndex = scaleIndex + 1;
			
			float deltaTime = (float)(nodeAnim->mScalingKeys[nextScaleIndex].mTime - nodeAnim->mScalingKeys[scaleIndex].mTime);
			float factor = (deltaTime == 0.f) ? 0.f : (tick - (float)nodeAnim->mScalingKeys[scaleIndex].mTime) / deltaTime;
			const aiVector3D& start = nodeAnim->mScalingKeys[scaleIndex].mValue;
			const aiVector3D& end = nodeAnim->mScalingKeys[nextScaleIndex].mValue;
			out = start + (end - start) * factor;
		}

		void comSkinedMesh::CalcInterpolatedRotation(aiQuaternion& out, float tick, const aiNodeAnim* nodeAnim)
		{
			if (nodeAnim->mNumRotationKeys == 1)
			{
				out = nodeAnim->mRotationKeys[0].mValue;
				return;
			}

			unsigned int rotationIndex = 0;

			for (unsigned int i = 0; i < nodeAnim->mNumRotationKeys - 1; i++)
			{
				if (tick < (float)nodeAnim->mRotationKeys[i + 1].mTime)
				{
					rotationIndex = i;
					break;
				}
			}

			unsigned int nextRotationIndex = rotationIndex + 1;

			float deltaTime = (float)(nodeAnim->mRotationKeys[nextRotationIndex].mTime - nodeAnim->mRotationKeys[rotationIndex].mTime);
			float factor = (deltaTime == 0.f) ? 0.f : (tick - (float)nodeAnim->mRotationKeys[rotationIndex].mTime) / deltaTime;
			const aiQuaternion& start = nodeAnim->mRotationKeys[rotationIndex].mValue;
			const aiQuaternion& end = nodeAnim->mRotationKeys[nextRotationIndex].mValue;
			aiQuaternion::Interpolate(out, start, end, factor);
			out = out.Normalize();
		}

		void comSkinedMesh::CalcInterpolatedPosition(aiVector3D& out, float tick, const aiNodeAnim* nodeAnim)
		{
			if (nodeAnim->mNumPositionKeys == 1)
			{
				out = nodeAnim->mPositionKeys[0].mValue;
				return;
			}

			unsigned int positionIndex = 0;

			for (unsigned int i = 0; i < nodeAnim->mNumPositionKeys - 1; i++)
			{
				if (tick < (float)nodeAnim->mPositionKeys[i + 1].mTime)
				{
					positionIndex = i;
					break;
				}
			}

			unsigned int nextPositionIndex = positionIndex + 1;

			float deltaTime = (float)(nodeAnim->mPositionKeys[nextPositionIndex].mTime - nodeAnim->mPositionKeys[positionIndex].mTime);
			float factor = (deltaTime == 0.f) ? 0.f : (tick - (float)nodeAnim->mPositionKeys[positionIndex].mTime) / deltaTime;
			const aiVector3D& start = nodeAnim->mPositionKeys[positionIndex].mValue;
			const aiVector3D& end = nodeAnim->mPositionKeys[nextPositionIndex].mValue;
			out = start + (end - start) * factor;
		}

		void comSkinedMesh::Draw()
		{
			if (material)
			{
				std::shared_ptr<Shader> shader = material->getShader();
				shader->use();

				std::vector<Math::Matrix4f> Transforms;
				BoneTransform(Transforms);

				for (unsigned int i = 0; i < Transforms.size(); i++)
				{
					char name[128];
					sprintf(name, "gbones[%d]", i);
					shader->setMat4(name, Transforms[i]);
				}

				material->Render();
			}
		}

		void comSkinedMesh::PlayAnim(std::string name, AnimMode m)
		{
			aiAnimation* anim = nullptr;
			for (unsigned int i = 0; i < scene->mNumAnimations; i++)
			{
				aiAnimation* a = scene->mAnimations[i];
				if (name == std::string(a->mName.C_Str()))
				{
					anim = a;
					activeAnim = i;
					break;
				}
			}

			if (!anim)
				return;

			mode = m;
			startTime = Service::Time().GetTimeSinceLaunch(TimePrecision::MILLISEC) / 1000.f;
		}

		void comSkinedMesh::PlayAnim(std::size_t index, AnimMode m)
		{
			aiAnimation* anim = nullptr;

			if (index < scene->mNumAnimations)
			{
				anim = scene->mAnimations[index];
				activeAnim = index;
			}

			if (!anim)
				return;

			mode = m;
			startTime = Service::Time().GetTimeSinceLaunch(TimePrecision::MILLISEC) / 1000.f;
		}
	}
}