#include "Vector4.h"
#include "Macros.h"
#include "Maths.h"

Vector4::Vector4()
{
	mX = VALUE_ZERO;
	mY = VALUE_ZERO;
	mZ = VALUE_ZERO;
	mW = VALUE_ZERO;
}

Vector4::Vector4(const float x, const float y, const float z, const float w)
{
	
	mX = x;
	mY = y;
	mZ = z;
	mW = w;
}


Vector4::~Vector4()
{
}

bool Vector4::operator==(const Vector4 & v)
{
	assert(IsNAN(v.mX) && IsNAN(v.mY) && IsNAN(v.mZ) && IsNAN(v.mW));
	if (AreAboutEqual(mX, v.mX) && AreAboutEqual(mY, v.mY) && AreAboutEqual(mZ, v.mZ) && AreAboutEqual(mW, v.mW)) {
		return true;
	}
	else {
		return false;
	}
}

bool Vector4::operator!=(const Vector4 & v)
{
	assert(IsNAN(v.mX) && IsNAN(v.mY) && IsNAN(v.mZ) && IsNAN(v.mW));
	if (mX != v.mX || mY != v.mY && mZ != v.mZ || mW != v.mW) {
		return true;
	}
	else {
		return false;
	}
}

Vector4 Vector4::operator+(const Vector4 & v) const
{
	assert(IsNAN(v.mX) && IsNAN(v.mY) && IsNAN(v.mZ) && IsNAN(v.mW));
	Vector4 sum;
	sum.mX = mX + v.mX;
	sum.mY = mY + v.mY;
	sum.mZ = mZ + v.mZ;
	sum.mW = mW + v.mW;
	return sum;
}

Vector4 Vector4::operator-(const Vector4 & v) const
{
	assert(IsNAN(v.mX) && IsNAN(v.mY) && IsNAN(v.mZ) && IsNAN(v.mW));
	Vector4 sub;
	sub.mX = mX - v.mX;
	sub.mY = mY - v.mY;
	sub.mZ = mZ - v.mZ;
	sub.mW = mW - v.mW;
	return sub;
}

Vector4 Vector4::operator*(const float f) const
{
	assert(IsNAN(f));
	Vector4 mul;
	mul.mX = f * mX;
	mul.mY = f * mY;
	mul.mZ = f * mZ;
	mul.mW = f * mW;
	return mul;
}

Vector4 Vector4::operator/(const float f) const
{
	assert(IsNAN(f));
	Vector4 div;
	div.mX = mX / f;
	div.mY = mY / f;
	div.mZ = mZ / f;
	div.mW = mW / f;
	return div;
}

Vector4 & Vector4::operator+=(const Vector4 & v)
{
	assert(IsNAN(v.mX) && IsNAN(v.mY) && IsNAN(v.mZ) && IsNAN(v.mW));
	this->mX = this->mX + v.mX;
	this->mY = this->mY + v.mY;
	this->mZ = this->mZ + v.mZ;
	this->mW = this->mW + v.mW;
	return *this;
}

Vector4 & Vector4::operator-=(const Vector4 & v)
{
	assert(IsNAN(v.mX) && IsNAN(v.mY) && IsNAN(v.mZ) && IsNAN(v.mW));
	this->mX = this->mX - v.mX;
	this->mY = this->mY - v.mY;
	this->mZ = this->mZ - v.mZ;
	this->mW = this->mW - v.mW;
	return *this;
}

Vector4 & Vector4::operator*=(const float f)
{
	assert(IsNAN(f));
	this->mX = this->mX * f;
	this->mY = this->mY * f;
	this->mZ = this->mZ * f;
	this->mW = this->mW * f;
	return *this;
}

Vector4 Vector4::inverse()
{
	this->mX = this->mX / (fabsf(this->mX)*fabsf(this->mX));
	this->mY = this->mY / (fabsf(this->mY)*fabsf(this->mY));
	this->mZ = this->mZ / (fabsf(this->mZ)*fabsf(this->mZ));
	this->mW = this->mW / (fabsf(this->mW)*fabsf(this->mW));
	return *this;
}
