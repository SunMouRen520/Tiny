#include "Camera.h"
#include "Tiny/Graphics/Object/Object.h"
#include "Tiny/Core/Service.h"
#include "Tiny/Math/Angle.h"

namespace Tiny {
	namespace Graphics {
		ComponentType comCamera::TYPE = ComponentType::Camera;


		comCamera* comCamera::New(Object* obj)
		{
			if (!obj)
			{
				Service::Log().W("Camera creation failed, obj null");
				return nullptr;
			}

			return new comCamera(obj, {1, 1}, 90, 1.f, 10000.f);
		}

		Math::Matrix4f comCamera::viewMatrix() const
		{
			Object* obj = GameObject();
			if (!obj)
				return Math::Matrix4f();
			
			Math::Vector3f right = obj->Transform().right();
			Math::Vector3f up = obj->Transform().up();
			Math::Vector3f forward = obj->Transform().forward();
			Math::Vector3f pos = obj->Transform().position();

			Math::Matrix4f rotMat = Math::Matrix4f(Math::Matrix3f(right, up, forward).Transpose());
			Math::Matrix4f posMat = Math::Matrix4f::Translation(-pos);
			
			return posMat * rotMat;
		}

		Math::Matrix4f comCamera::perspectMatrix() const
		{
			return Math::Matrix4f::Perspective(fov, aspect, near_plane, far_plane);
		}

		void comCamera::setSimpleMode(Object* tar)
		{
			if (!tar)
				return;

			camType = CAM_TYPE::SIMPLE;
			theta = theta_init;
			alpha = alpha_init;
			distance = dis_init;
			target = tar;

			Object* obj = GameObject();
			Transformf& transform = obj->Transform();

			alpha = Math::Degf(alpha);
			theta = Math::Degf(theta);

			float x = distance * std::sin(float(Math::Radf(theta))) * std::cos(float(Math::Radf(alpha)));
			float y = distance * std::cos(float(Math::Radf(theta)));
			float z = distance * std::sin(float(Math::Radf(theta))) * std::sin(float(Math::Radf(alpha)));

			transform.setPosition(target->Transform().position() + Math::Vector3f(x, y, z));

			Math::Vector3f forward = target->Transform().position() - transform.position();
			Math::Vector3f right = Math::Cross(Math::Vector3f::YAxis(), forward);
			Math::Vector3f up = Math::Cross(forward, right);
			Math::Matrix3f rotMat = Math::Matrix3f(right.Normalize(), up.Normalize(), forward.Normalize());
			
			transform.setEulerAngles(Math::Matrix3f::ToEuler(rotMat));
		}

		void comCamera::Rotate(float x, float y)
		{
			Object* obj = GameObject();
			if (!obj)
				return;

			Transformf& transform = obj->Transform();

			if (camType == CAM_TYPE::FREE_3D)
			{
				Math::Vector3f haxis = transform.right();
				Math::Vector3f vaxis = Math::Vector3f::YAxis();

				transform.Rotate(haxis, Math::Degf(y));
				transform.Rotate(vaxis, Math::Degf(-x));
			}
			else if (camType == CAM_TYPE::SIMPLE)
			{
				if (!target) // unbind target
					return;

				float speed = 0.2f;
				float degalpha = float(alpha);
				float degtheta = float(theta);
				degalpha = fmod(float(degalpha) + -x * speed, 360.f);
				degtheta = degtheta + y * speed;

				if (degtheta <= 1)
					degtheta = 1;
				if (degtheta >= 179)
					degtheta = 179;

				alpha = Math::Degf(degalpha);
				theta = Math::Degf(degtheta);

				float x = distance * std::sin(float(Math::Radf(theta))) * std::cos(float(Math::Radf(alpha)));
				float y = distance * std::cos(float(Math::Radf(theta)));
				float z = distance * std::sin(float(Math::Radf(theta))) * std::sin(float(Math::Radf(alpha)));
			
				transform.setPosition(target->Transform().position() + Math::Vector3f(x, y, z));
				Math::Vector3f forward = target->Transform().position() - transform.position();
				Math::Vector3f right = Math::Cross(Math::Vector3f::YAxis(), forward);
				Math::Vector3f up = Math::Cross(forward, right);

				Math::Matrix3f rotMat = Math::Matrix3f(right.Normalize(), up.Normalize(), forward.Normalize());
				transform.setEulerAngles(Math::Matrix3f::ToEuler(rotMat));
			}
		}

		void comCamera::Translate(float x, float y, float z)
		{
			if (camType != CAM_TYPE::FREE_3D)
				return;

			Object* obj = GameObject();
			if (!obj)
				return;

			Transformf& transform = obj->Transform();

			Math::Vector3f xaxis = transform.right();
			Math::Vector3f yaxis = transform.up();
			Math::Vector3f zaxis = transform.forward();

			transform.Translate((xaxis*x) + (yaxis*y) + (zaxis*z));
		}
	}
}