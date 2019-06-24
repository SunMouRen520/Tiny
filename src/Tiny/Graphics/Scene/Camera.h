#ifndef _TINY_CAMERA_H
#define _TINY_CAMERA_H

#include "Tiny/Graphics/Object/Component.h"
#include "Tiny/Math/Vector4.h"
#include "Tiny/Math/Matrix4.h"
#include "Tiny/Math/MathForward.h"

namespace Tiny {
	namespace Graphics {
		class comCamera :public Component
		{
			const float dis_init = 20.f;
			const float theta_init = 90.f;
			const float alpha_init = 0.f;

			friend class Object;
		public:
			enum class CAM_TYPE
			{
				SIMPLE,
				FREE_3D,
			};
			static ComponentType TYPE;
			comCamera(const comCamera&) = delete;
			comCamera& operator=(const comCamera&) = delete;
		public:
			//cam type
			CAM_TYPE type() { return camType; }
			//set simple mode
			void setSimpleMode(Object* target);
			//set free3d mode
			void setFree3DMode() { camType = CAM_TYPE::FREE_3D; }
			//simple mode target set
			void setTargetObject(Object* obj) { target = obj; }
			//x-horizontal, y-vertical
			void Rotate(float x, float y);
			//x-right, y-up, z-forward
			void Translate(float x, float y, float z);
		public:
			Math::Matrix4f viewMatrix() const;
			Math::Matrix4f perspectMatrix() const;
		private:
			//only called by Object
			static comCamera* New(Object*);
			comCamera(Object* obj, Math::Vector2i rect, float angle, float n, float f) :Component(ComponentType::Camera, obj), view_rect(rect), fov(angle), near_plane(n), far_plane(f) { aspect = (float)rect.Y() / (float)rect.X(); }
			//cam attri
			Math::Vector2i view_rect;
			float near_plane;
			float far_plane;
			float aspect;
			Math::Degf fov;
			CAM_TYPE camType = CAM_TYPE::FREE_3D;
		//simple mode
		public:
			//the distance between target and camera in simple mode
			float distance = dis_init;
		private://simple mode
			//target
			Object* target = nullptr;
			//polar coordinate system
			Math::Degf theta = theta_init; //angle with positive y axis, range(1-179)
			Math::Degf alpha = alpha_init; //angle with positive x axis, range(0-359)
		};
	}
}

#endif