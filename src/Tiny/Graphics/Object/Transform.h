#ifndef _TINY_TRANSFORM_H
#define _TINY_TRANSFORM_H

#include "Tiny/Math/Vector4.h"
#include "Tiny/Math/Matrix4.h"
#include "Tiny/Math/Quaternion.h"
#include "Component.h"

/*
  Transform, same as unity transfom component
  rotate, order by z, x, y
*/

namespace Tiny {
	namespace Graphics {
		template <typename T>
		class Transform:public Component
		{
			template<typename T> friend class Transform;
		public:
			Transform() :Component(ComponentType::Transform), Pos(), Rot(), Scale(1), parent(nullptr) {};
			Transform(Object* objptr) :Component(ComponentType::Transform, objptr), Pos(), Rot(), Scale(1), parent(nullptr) {};
			~Transform() = default;
			//Set Position
			void setPosition(const Math::Vector3<T>& pos) { Pos = pos; }
			//Set EulerAngles
			void setEulerAngles(const Math::Vector3<T>& rot) { Rot = rot; }
			//Set Scale
			void setScale(const Math::Vector3<T>& scale) { Scale = scale; }
			//Position of the transform relative to the parent transform
			Math::Vector3<T> localPosition() const { return Pos; }
			//The rotation as Euler angles in degrees relative to the parent transform's rotation
			Math::Vector3<T> localEulerAngles() const { return Rot; }
			//The scale of the transform relative to the parent
			Math::Vector3<T> localScale() const { return Scale; }
			//The rotation of the transform relative to the parent transform's rotation
			//localRotation and localRotationByEuler, i didn't know which was faster, so i wrote two implementations 
			Math::Quaternion<T> localRotation() const;
			Math::Quaternion<T> localRotationByEuler() const;
			//The position of the transform in world space
			Math::Vector3<T> position() const;
			//The rotation as Euler angles in degrees
			Math::Vector3<T> eulerAngles() const;
			//The scale of the transform in world space
			Math::Vector3<T> scale() const;
			//The rotation of the transform in world space stored as a Quaternion
			Math::Quaternion<T> rotation() const;
			//Transform direction x
			Math::Vector3<T> right() const;
			//Transform direction y
			Math::Vector3<T> up() const;
			//Transform direction z
			Math::Vector3<T> forward() const;
			//Matrix that transforms a point from local space into world space
			Math::Matrix4<T> localToWorldMatrix() const;
			//Matrix that transforms a point from world space into local space
			Math::Matrix4<T> worldToLocalMatrix() const;
			//set parent
			bool SetParent(Transform* ptr) { parent = (ptr != nullptr) ? ptr : nullptr; return (ptr != nullptr); }
			//get parent
			Transform* Parent() const { return parent; }
			//get root
			Transform* Root() const;
		public:
			//Moves the transform in the direction and distance of translation
			void Translate(Math::Vector3<T> translation) { Pos += translation; };
			//Applies a rotation of eulerAngles, order by z, x, y
			void Rotate(Math::Vector3<T> eulerAngles) { Rot += eulerAngles };
			//Rotates the transform around axis by angle degrees
			void Rotate(Math::Vector3<T> axis, Math::Deg<T> angle);
		public:
			Transform & operator=(const Transform& src) { Pos = src.Pos; Rot = src.Rot; Scale = src.Scale; };
		private:
			Math::Vector3<T> Pos;
			Math::Vector3<T> Rot; //EulerAngles,order by zxy, same as unity
			Math::Vector3<T> Scale;

			Transform* parent;
		};
		//order by zxy
		template <typename T> Math::Quaternion<T> Transform<T>::localRotation() const
		{
			Math::Quaternion<T> qres = Math::Quaternion<T>::Rotate(Math::Deg<T>(Rot.Z()), Math::Vector3<T>::ZAxis());
			qres *= Math::Quaternion<T>::Rotate(Math::Deg<T>(Rot.X()), Math::Vector3<T>::XAxis());
			qres *= Math::Quaternion<T>::Rotate(Math::Deg<T>(Rot.Y()), Math::Vector3<T>::YAxis());

			return qres;
		}
		//Euler->Quaternion
		template <typename T> Math::Quaternion<T> Transform<T>::localRotationByEuler() const
		{
			return Math::Quaternion<T>::FromEuler(Rot);
		}

		template <typename T> Math::Vector3<T> Transform<T>::position() const
		{
			return parent ? parent->position() + Pos : Pos;
		}

		template <typename T> Math::Vector3<T> Transform<T>::eulerAngles() const
		{
			return rotation().ToEuler();
		}

		template <typename T> Math::Vector3<T> Transform<T>::scale() const
		{
			if (parent)
			{
				Math::Vector3<T> _parent = parent->scale();
				Math::Vector3<T> _local = Scale;
				return Math::Vector3<T>(_parent.X()*_local.X(), _parent.Y()*_local.Y(), _parent.Z()*_local.Z());
			}
			else
				return Scale;
		}

		template <typename T> Math::Quaternion<T> Transform<T>::rotation() const
		{
			return parent ? localRotation() * parent->rotation() : localRotation();
		}

		template <typename T> Math::Vector3<T> Transform<T>::right() const
		{
			return rotation().Tranform(Math::Vector3<T>::XAxis());
		}

		template <typename T> Math::Vector3<T> Transform<T>::up() const
		{
			return rotation().Tranform(Math::Vector3<T>::YAxis());
		}

		template <typename T> Math::Vector3<T> Transform<T>::forward() const
		{
			return rotation().Tranform(Math::Vector3<T>::ZAxis());
		}

		template <typename T> Transform<T>* Transform<T>::Root() const
		{
			return parent ? parent->Root() : this;
		}

		template <typename T> Math::Matrix4<T> Transform<T>::localToWorldMatrix() const
		{
			Math::Vector3<T> _pos = localPosition();
			Math::Vector3<T> _scale = localScale();
			Math::Matrix3<T> _rotMat = localRotation().ToMatrix();

			Math::Matrix4<T> _matRes(_rotMat);
			_matRes[0][0] *= _scale[0];
			_matRes[1][1] *= _scale[1];
			_matRes[2][2] *= _scale[2];
			_matRes[3][0] += _pos[0];
			_matRes[3][1] += _pos[1];
			_matRes[3][2] += _pos[2];

			return parent ? _matRes *  parent->localToWorldMatrix() : _matRes;
		}

		template <typename T> Math::Matrix4<T> Transform<T>::worldToLocalMatrix() const
		{
			return localToWorldMatrix().Inverse();
		}

		template <typename T> void Transform<T>::Rotate(Math::Vector3<T> axis, Math::Deg<T> angle)
		{
			Math::Quaternion<T> rotate = Math::Quaternion<T>::Rotate(angle, axis);
			Rot = (localRotation() * rotate).ToEuler();
		}
	}
}

#endif