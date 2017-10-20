#pragma once
#include "Vector3.h"
#include <xmmintrin.h> 
#include <intrin.h>
#include<stdio.h>
#include "Profiler.h"

/*print the vector*/

inline void Vector3::print() {
	printf("< %f, %f, %f >", X(), Y(), Z());
}

inline float Vector3::X() const
{
	return mX;
}

inline float Vector3::Y() const
{
	return mY;
}

inline float Vector3::Z() const
{
	return mZ;
}

inline void Vector3::SetX(const float x)
{
	mX = x;
}

inline void Vector3::SetY(const float y)
{
	mY = y;
}

inline void Vector3::SetZ(const float z)
{
	mZ = z;
}

/*input the vector*/
inline void Vector3::input() {
	printf("Enter x coordinate ");
	scanf_s("%f", &mX);
	printf("Enter y coordinate ");
	scanf_s("%f", &mY);
	printf("Enter z coordinate ");
	scanf_s("%f", &mZ);
}

inline float dot(const SIMDVector3 & i_lhs, SIMDVector3 & i_rhs)
{
	return _mm_cvtss_f32(_mm_dp_ps(i_lhs.m_vec, i_rhs.m_vec, 0x71));
}

inline Vector3 cross(const Vector3 & i_lhs, const Vector3 & i_rhs)
{
	return Vector3(i_lhs.Y() * i_rhs.Z() - i_lhs.Z() * i_rhs.Y(),
		i_lhs.Z() * i_rhs.X() - i_lhs.X() * i_rhs.Z(),
		i_lhs.X() * i_rhs.Y() - i_lhs.Y() * i_rhs.X());
}


inline Vector3 cross(const SIMDVector3 & i_lhs, const SIMDVector3 & i_rhs)
{
	SIMDVector3 crossProd(_mm_sub_ps(
		_mm_mul_ps(_mm_shuffle_ps(i_lhs.m_vec, i_lhs.m_vec, _MM_SHUFFLE(3, 0, 2, 1)), _mm_shuffle_ps(i_rhs.m_vec, i_rhs.m_vec, _MM_SHUFFLE(3, 1, 0, 2))),

		_mm_mul_ps(_mm_shuffle_ps(i_lhs.m_vec, i_lhs.m_vec, _MM_SHUFFLE(3, 1, 0, 2)), _mm_shuffle_ps(i_rhs.m_vec, i_rhs.m_vec, _MM_SHUFFLE(3, 0, 2, 1)))
	));
	//__m128 
	return Vector3(crossProd.m_x, crossProd.m_y,crossProd.m_z);

}

inline float dot(const Vector3 & i_lhs, const Vector3 & i_rhs)
{	
	__m128 vec0 = { i_lhs.X(), i_lhs.Y(), i_lhs.Z(), 0.0f };
	__m128 vec1 = { i_rhs.X(), i_rhs.Y(), i_rhs.Z(), 0.0f };

	// do the dot product of the first 3 components – the 7 part of 0x71
	// output result to only lower float of output  - the 1 part of 0x71
	__m128 vec2 = _mm_dp_ps(vec0, vec1, 0x71);

	float dot = _mm_cvtss_f32(vec2);

	return dot;
}

