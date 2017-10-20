#pragma once
class Vector4
{
public:
	Vector4();
	Vector4(const float x, const float y,const float z, const float w);
	~Vector4();

	bool operator==(const Vector4& v);
	bool operator!=(const Vector4& v);
	Vector4 operator+(const Vector4& v) const;
	Vector4 operator-(const Vector4& v) const;
	Vector4 operator*(const float f) const;
	Vector4 operator/(const float f) const;
	Vector4& operator+=(const Vector4& v);
	Vector4& operator-=(const Vector4& v);
	Vector4& operator*=(const float f);
	Vector4 inverse();

	//static variables
	static Vector4 zero;
	static Vector4 one;
	static Vector4 right;
	static Vector4 left;
	static Vector4 up;
	static Vector4 down;

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
	inline void SetW(const float f);

private:
	float mX;
	float mY;
	float mZ;
	float mW;
};

#include "Vector4-inl.h"

