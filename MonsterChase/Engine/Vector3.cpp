#include "Vector3.h"
#include "Macros.h"
#include "Maths.h"

Vector3::Vector3()
{
	mX = VALUE_ZERO;
	mY = VALUE_ZERO;
	mZ = VALUE_ZERO;
}

Vector3::Vector3(const float x, const float y, const float z)
{
	assert(IsNAN(x));
	assert(IsNAN(y));
	mX = x;
	mY = y;
	mZ = z;
}


Vector3::~Vector3()
{
}

bool Vector3::operator==(const Vector3 & v)
{
	assert(IsNAN(v.mX) && IsNAN(v.mY) && IsNAN(v.mZ));
	if (AreAboutEqual(mX, v.mX) && AreAboutEqual(mY, v.mY) && AreAboutEqual(mZ, v.mZ)) {
		return true;
	}
	else {
		return false;
	}
}

bool Vector3::operator!=(const Vector3 & v)
{
	assert(IsNAN(v.mX) && IsNAN(v.mY) && IsNAN(v.mZ));
	if (mX != v.mX || mY != v.mY && mZ != v.mZ) {
		return true;
	}
	else {
		return false;
	}
}

Vector3 Vector3::operator+(const Vector3 & v) const
{
	assert(IsNAN(v.mX) && IsNAN(v.mY) && IsNAN(v.mZ));
	Vector3 sum;
	sum.mX = mX + v.mX;
	sum.mY = mY + v.mY;
	sum.mZ = mZ + v.mZ;
	return sum;
}

Vector3 Vector3::operator-(const Vector3 & v) const
{
	assert(IsNAN(v.mX) && IsNAN(v.mY) && IsNAN(v.mZ));
	Vector3 sub;
	sub.mX = mX - v.mX;
	sub.mY = mY - v.mY;
	sub.mZ = mZ - v.mZ;
	return sub;
}

Vector3 Vector3::operator*(const float f) const
{
	assert(IsNAN(f));
	Vector3 mul;
	mul.mX = f * mX;
	mul.mY = f * mY;
	mul.mZ = f * mZ;
	return mul;
}

float Vector3::operator*(const Vector3 v1) const
{	
	SIMDVector3 i_lhs = SIMDVector3(this->mX,this->mY, this->mZ);
	SIMDVector3 r_lhs = SIMDVector3(v1.mX, v1.mY, v1.mZ);
	return dot(i_lhs, r_lhs);
	//return (this->mX * v1.mX) + (this->mY * v1.mY) + (this->mZ * v1.mZ);
}

Vector3 Vector3::operator/(const float f) const
{
	assert(IsNAN(f));
	Vector3 div;
	div.mX = mX / f;
	div.mY = mY / f;
	div.mZ = mZ / f;
	return div;
}

Vector3 & Vector3::operator+=(const Vector3 & v)
{
	assert(IsNAN(v.mX) && IsNAN(v.mY) && IsNAN(v.mZ));
	this->mX = this->mX + v.mX;
	this->mY = this->mY + v.mY;
	this->mZ = this->mZ + v.mZ;
	return *this;
}

Vector3 & Vector3::operator-=(const Vector3 & v)
{
	assert(IsNAN(v.mX) && IsNAN(v.mY) && IsNAN(v.mZ));
	this->mX = this->mX - v.mX;
	this->mY = this->mY - v.mY;
	this->mZ = this->mZ - v.mZ;
	return *this;
}

Vector3 & Vector3::operator*=(const float f)
{
	assert(IsNAN(f));
	this->mX = this->mX * f;
	this->mY = this->mY * f;
	this->mZ = this->mZ * f;
	return *this;
}

Vector3 Vector3::inverse()
{
	this->mX = this->mX / (fabsf(this->mX)*fabsf(this->mX));
	this->mY = this->mY / (fabsf(this->mY)*fabsf(this->mY));
	this->mZ = this->mZ / (fabsf(this->mZ)*fabsf(this->mZ));
	return *this;
}



