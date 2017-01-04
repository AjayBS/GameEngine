#include "Point2.h"
#include "Macros.h"
#include "Maths.h"
namespace Engine {
	/*static variables*/
	Point2 Point2::zero = Point2(0, 0);
	Point2 Point2::right = Point2(1, 0);
	Point2 Point2::left = Point2(-1, 0);
	Point2 Point2::up = Point2(0, 1);
	Point2 Point2::down = Point2(0, -1);

	/*default vector of <0,0,0>*/
	Point2::Point2() {
		mX = VALUE_ZERO;
		mY = VALUE_ZERO;
	}

	/*vector which takes in parameters*/
	Point2::Point2(const float x, const float y) {
		assert(IsNAN(x));
		assert(IsNAN(y));
		mX = x;
		mY = y;
	}

	/*Check if 2 vectors are equal or not*/
	bool Point2::operator==(const Point2& v) {
		assert(IsNAN(v.mX) && IsNAN(v.mY));
		if (AreAboutEqual(mX, v.mX) && AreAboutEqual(mY, v.mY)) {
			return true;
		}
		else {
			return false;
		}
	}

	bool Point2::operator!=(const Point2& v) {
		assert(IsNAN(v.mX) && IsNAN(v.mY));
		if (mX != v.mX || mY != v.mY) {
			return true;
		}
		else {
			return false;
		}
	}

	/*addition of 2 vectors (+ operator)*/
	Point2 Point2::operator+(const Point2& v) const {
		assert(IsNAN(v.mX) && IsNAN(v.mY));
		Point2 sum;
		sum.mX = mX + v.mX;
		sum.mY = mY + v.mY;
		return sum;
	}


	/*addition of 2 vectors (+= operator)*/
	Point2& Point2::operator+=(const Point2& v){
		assert(IsNAN(v.mX) && IsNAN(v.mY));
		this->mX = this->mX + v.mX;
		this->mY = this->mY + v.mY;
		return *this;
	}

	/*subtraction of 2 vectors (- operator)*/
	Point2 Point2::operator-(const Point2& v) const {
		assert(IsNAN(v.mX) && IsNAN(v.mY));
		Point2 sub;
		sub.mX = mX - v.mX;
		sub.mY = mY - v.mY;
		return sub;
	}

	/*addition of 2 vectors (-= operator)*/
	Point2& Point2::operator-=(const Point2& v) {
		assert(IsNAN(v.mX) && IsNAN(v.mY));
		this->mX = this->mX - v.mX;
		this->mY = this->mY - v.mY;
		return *this;
	}

	/*multiplication of vectors (* operator)*/
	Point2 Point2::operator*(const float f) const {
		assert(IsNAN(f));
		Point2 mul;
		mul.mX = f * mX;
		mul.mY = f * mY;
		return mul;
	}

	/*multiplication of vectors (*= operator)*/
	Point2& Point2::operator*=(const float f) {
		assert(IsNAN(f));
		this->mX = this->mX * f;
		this->mY = this->mY * f;
		return *this;
	}

	/*inverse of the current vector*/
	Point2 Point2::inverse() {
		this->mX = this->mX / (fabsf(this->mX)*fabsf(this->mX));
		this->mY = this->mY / (fabsf(this->mY)*fabsf(this->mY));
		return *this;
	}

	Point2::~Point2() {}
}