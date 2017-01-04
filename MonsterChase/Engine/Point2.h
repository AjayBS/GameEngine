#pragma once
#include<stdio.h>
#include<math.h>
namespace Engine {

	class Point2 {

	public:
		Point2();
		Point2(const float x, const float y);
		~Point2();

		bool operator==(const Point2& v);
		bool operator!=(const Point2& v);
		Point2 operator+(const Point2& v) const;
		Point2 operator-(const Point2& v) const;
		Point2 operator*(const float f) const;
		Point2& operator+=(const Point2& v);
		Point2& operator-=(const Point2& v);
		Point2& operator*=(const float f);
		Point2 inverse();

		//static variables
		static Point2 zero;
		static Point2 one;
		static Point2 right;
		static Point2 left;
		static Point2 up;
		static Point2 down;

		inline void print();
		inline void input();

		//getters
		inline float GetPositionX() const;
		inline float GetPositionY() const;

		//setters
		inline void SetPositionX(const float f);
		inline void SetPositionY(const float f);

	private:
		float mX;
		float mY;
	};

}

#include "Point2-inl.h"