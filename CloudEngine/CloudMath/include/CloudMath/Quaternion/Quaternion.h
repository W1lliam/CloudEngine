/**
* Project CloudMath
* @author CloudTech
* @version 1.0.0
*/

#pragma once
#ifndef _QUATERNION_H
#define _QUATERNION_H

#include "CloudMath/CloudMathAPI.h"
#include "CloudMath/Vector/Vector3.h"
#include "CloudMath/Matrix/Matrix3.h"
#include "CloudMath/Matrix/Matrix4.h"

namespace CloudMath
{
	class CLOUDMATH_API Quaternion
	{
	private:
		float m_x;
		float m_y;
		float m_z;
		//m_w is the real value of quaternion, this will be used to check if the quaternion is pure/identity or not.
		float m_w;

	public:
		static Quaternion Identity();

#pragma region Constructors & Assignment

		Quaternion();
		/**
		* @param p_x Vector part of Quaternion
		* @param p_y Vector part of Quaternion
		* @param p_z Vector part of Quaternion
		* @param p_w Real value of Quaternion
		*
		* In pure/applied Maths, we write W (or real), (Xi + Yj + Zk) (or Vector)
		*/
		Quaternion(float p_x, float p_y, float p_z, float p_w);
		/**
		* Copy Constructor
		* @param p_other
		*/
		Quaternion(const Quaternion& p_other);

		/**
		* Construct from rotation matrix
		* @param p_matrix Rotation matrix
		*/
		explicit Quaternion(const Matrix3<float>& p_matrix);
		/**
		* Construct from rotation matrix
		* @param p_matrix Rotation matrix
		*/
		explicit Quaternion(const Matrix4<float>& p_matrix);

		/**
		* @param p_axis
		* @param p_angle in degrees
		*/
		Quaternion(const Vector3<float>& p_axis, float p_angle);

		/**
		 * Construct from euler angles
		 * @param p_yawZ Angle around Z
		 * @param p_pitchY Angle around Y
		 * @param p_rollX Angle around X 
		 */
		Quaternion(const float& p_yawZ, const float& p_pitchY, const float& p_rollX);

		/**
		* Construct from euler angles
		* @param p_eulerAngle
		*/
		Quaternion(const Vector3f& p_eulerAngle);

#pragma endregion

#pragma region Tests & Comparisons

		/**
		* Check If the quaternion is Identity
		* if the quaternion has no rotation(meaning x,y,z axis values = 0), it's Identity
		*/
		bool IsIdentity() const;

		/*
		* Check if the quaternion is pure
		* if the quaternion has no real value(meaning real part = 0), it's pure
		*/
		bool IsPure() const;

		/*
		* Check if the quaternion is Normalized
		* if the quaternion length = 1, it's normalized
		*/
		bool IsNormalized() const;

		bool operator==(const Quaternion& p_otherQuat) const;
		bool operator!=(const Quaternion& p_otherQuat) const;

#pragma endregion
#pragma region Arithmetic Operations

#pragma region Add
		Quaternion operator+(const Quaternion& p_otherQuat) const;
		Quaternion& operator+=(const Quaternion& p_otherQuat);

#pragma endregion
#pragma region Substract
		Quaternion operator-(const Quaternion& p_otherQuat) const;
		Quaternion& operator-=(const Quaternion& p_otherQuat);

#pragma endregion
#pragma region Multiply

		float DotProduct(const Quaternion& p_otherQuat) const;
		static float DotProduct(const Quaternion& p_left, const Quaternion& p_right);

		/*
		* operator overload for DotProduct
		*/
		float operator|(const Quaternion& p_otherQuat) const;

		Quaternion& operator*=(const float p_scale);
		Quaternion operator*(const float p_scale) const;

		Quaternion operator*(const Quaternion& p_otherQuat) const;
		Quaternion& operator*=(const Quaternion& p_otherQuat);

		Vector3<float> operator*(const Vector3<float>& p_toMultiply) const;
		Matrix3<float> operator*(const Matrix3<float>& p_multiply) const;

#pragma endregion
#pragma region Divide
		Quaternion& operator/=(const float p_scale);
		Quaternion operator/(const float p_scale) const;

#pragma endregion
#pragma endregion

#pragma region Quaternion Operations
		Quaternion& Normalize();
		static Quaternion Normalize(const Quaternion& p_quaternion);

		float Length() const;
		float LengthSquare() const;
		float GetAngle() const;

		Quaternion& Inverse();
		static Quaternion Inverse(const Quaternion& p_quaternion);

		Quaternion& Conjugate();
		static Quaternion Conjugate(const Quaternion& p_quaternion);

		Quaternion& Square();
		static Quaternion Square(const Quaternion& p_quaternion);

		/**
		* @param p_axis
		* @param p_angle
		*/
		void GetAxisAndAngle(Vector3<float>& p_axis, float& p_angle) const;

		Vector3<float> GetAxisZ() const;
		Vector3<float> GetAxisY() const;
		Vector3<float> GetAxisX() const;

		Vector3<float> GetForwardVector() const;
		Vector3<float> GetRightVector() const;
		Vector3<float> GetUpVector() const;
		Vector3<float> GetRotationAxis() const;

		/**
		* @param p_other
		* Caculate the angle between two quaternions.
		*/
		float AngularDistance(const Quaternion& p_other) const;

		float GetXAxisValue() const;
		float GetYAxisValue() const;
		float GetZAxisValue() const;
		float GetRealValue() const;

		void SetXAxisValue(float p_xValue);
		void SetYAxisValue(float p_yValue);
		void SetZAxisValue(float p_zValue);
		void SetRealValue(float p_realValue);

		/**
		* @param p_first Start of Lerp, should be normalized
		* @param p_second End of Lerp, should be normalized
		* @param p_alpha
		*/
		static Quaternion Lerp(Quaternion& p_first, Quaternion& p_second, const float p_alpha);

		/**
		* @param p_first start of Slerp, should be normalized
		* @param p_second end of Slerp, should be normalized
		* @param p_alpha
		*/
		static Quaternion Slerp(Quaternion& p_first, Quaternion& p_second, const float p_alpha);
		/**
		* @param p_first Start of NLerp, should be normalized
		* @param p_second End of NLerp, should be normalized
		* @param p_alpha
		*/
		static Quaternion Nlerp(Quaternion& p_first, Quaternion& p_second, const float p_alpha);
		/**
		* @param p_position
		* @param p_pivot
		* p_position is the point that you want to rotate
		* p_pivot is the center of rotation
		* p_eulerAngles is the angle, how much you want to rotate.
		*/
		Vector3<float> RotateRelativeToPivot(const Vector3<float>& p_position, const Vector3<float>& p_pivot) const;
		/**
		* @param p_position Point that you want to rotate
		* @param p_pivot Center of rotation
		* @param p_eulerAngles The angle, how much you want to rotate.
		*/
		static Vector3<float> RotateRelativeToPivot(const Vector3<float>& p_position, const Vector3<float>& p_pivot,
			const Vector3<float>& p_eulerAngles);
		/**
		* @param p_position Point that you want to rotate
		* @param p_pivot Center of rotation
		* @param p_quaternion The angle, how much you want to rotate
		*/
		static Vector3<float> RotateRelativeToPivot(const Vector3<float>& p_position, const Vector3<float>& p_pivot,
			Quaternion& p_quaternion);

		/**
		* Rotate Vector by Quaternion, qpq^-1
		* @param p_toRotate
		*/
		Vector3<float> RotateVector(const Vector3<float>& p_toRotate) const;

#pragma endregion
#pragma region Conversions
		/**
		* Returning Euler axis angles for each axis.
		* First value of returned vector = X axis, second, Y axis, and third, Z axis.
		*/
		Vector3<float> ToEuler() const;
		std::string ToString() const;
		static std::string ToString(const Quaternion& p_quaternion);
		Matrix3<float> ToMatrix3() const;
		/**
		* Convert Quaternion into 4x4 Matrix.
		* It will be used as rotation matrix instead of euler axis rotation matrices.
		*/
		Matrix4<float> ToMatrix4() const;
#pragma endregion
	};

	CLOUDMATH_API std::ostream& operator<<(std::ostream& p_stream, const Quaternion& p_quaternion);
}
#endif //_QUATERNION_H
