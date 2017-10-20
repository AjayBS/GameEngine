#include "Vector4.h"
#include<stdio.h>
#pragma once
/*print the vector*/

inline void Vector4::print() {
	printf("< %f, %f >", X(), Y());
}

inline float Vector4::X() const
{
	return mX;
}

inline float Vector4::Y() const
{
	return mY;
}

inline float Vector4::Z() const
{
	return mZ;
}

inline float Vector4::W() const
{
	return mW;
}

inline void Vector4::SetX(const float x)
{
	mX = x;
}

inline void Vector4::SetY(const float y)
{
	mY = y;
}

inline void Vector4::SetZ(const float z)
{
	mZ = z;
}

inline void Vector4::SetW(const float w)
{
	mW = w;
}

/*input the vector*/
inline void Vector4::input() {
	printf("Enter x coordinate ");
	scanf_s("%f", &mX);
	printf("Enter y coordinate ");
	scanf_s("%f", &mY);
	printf("Enter z coordinate ");
	scanf_s("%f", &mZ);
	printf("Enter w coordinate ");
	scanf_s("%f", &mW);
}

