#pragma once
//Whgat
#include <xmmintrin.h> 
#include <intrin.h>
class Vector3
{
public:
	Vector3();
	Vector3(const float x, const float y, const float z);
	

	~Vector3();

	bool operator==(const Vector3& v);
	bool operator!=(const Vector3& v);
	Vector3 operator+(const Vector3& v) const;
	Vector3 operator-(const Vector3& v) const;
	Vector3 operator*(const float f) const;
	float operator*(const Vector3 f) const;
	Vector3 operator/(const float f) const;
	Vector3& operator+=(const Vector3& v);
	Vector3& operator-=(const Vector3& v);
	Vector3& operator*=(const float f);
	Vector3 inverse();
	



	//static variables
	static Vector3 zero;
	static Vector3 one;
	static Vector3 right;
	static Vector3 left;
	static Vector3 up;
	static Vector3 down;

	inline void print();
	inline void input();

	//getters
	inline float X() const;
	inline float Y() const;
	inline float Z() const;
	inline float W() const;

	//setters
	inline void SetX(const float f);
	inline void SetY(const float f);
	inline void SetZ(const float f);

private:
	float mX;
	float mY;
	float mZ;
	
};

class SIMDVector3
{
	friend float dot(const SIMDVector3 & i_lhs, SIMDVector3 & i_rhs);
	friend Vector3 cross(const SIMDVector3 & i_lhs, const SIMDVector3 & i_rhs);
public:
	SIMDVector3(float i_x, float i_y, float i_z) :
		m_vec(_mm_set_ps(0, i_z, i_y, i_x))
	{}
	SIMDVector3(const __m128 i_vec) :
		m_vec(i_vec)
	{}

private:
	union {
		struct {
			float 	m_x, m_y, m_z;
		};
		__m128 	m_vec; 		// This will align us to 16 bytes because __m128 is
	};
};



inline float dot(const Vector3 & i_lhs, const Vector3 & i_rhs);
inline Vector3 cross(const Vector3 & i_lhs, const Vector3 & i_rhs);
#include "Vector3-inl.h"