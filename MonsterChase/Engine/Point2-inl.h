#pragma once
/*print the vector*/
using namespace Engine;

inline void Point2::print() {
	printf("< %f, %f >", GetPositionX(), GetPositionY());
}

/*input the vector*/
inline void Point2::input() {
	printf("Enter x coordinate ");
	scanf_s("%f", &mX);
	printf("Enter y coordinate ");
	scanf_s("%f", &mY);
}

/*getter functionss*/
inline float Point2::GetPositionX() const{
	return mX;
}

inline float Point2::GetPositionY() const{
	return mY;
}

inline void Point2::SetPositionX(const float x) {
	mX = x;
}

inline void Point2::SetPositionY(const float y) {
	mY = y;
}
