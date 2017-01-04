#include "Math.h"
#include "Maths.h"
#include <stdlib.h>

int Random(const int lower_range,const int higher_range) {
	return rand() % higher_range + (lower_range);
}

bool IsNAN(const float i_val) 
{
	volatile float val = i_val;
	return val != val;
}

bool AreAboutEqual(const float i_lhs, const float i_rhs)
{
	const float epsilon = .0001f;
	return fabs(i_rhs - i_lhs) < epsilon;
}

bool AreAboutEqual(const float i_lhs, const float i_rhs, const float epsilon)
{
	return fabs(i_rhs - i_lhs) < epsilon;
}

