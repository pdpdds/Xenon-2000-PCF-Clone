#pragma once
#include <math.h>

class MathLibrary
{
public:

	const float PI = 3.141592654f;

	inline static float Abs(float v)
	{
		return v >= 0.f ? v : -v;
	}

	inline static float SquareRoot(float a)
	{
		return (float) sqrt((double) a);
	}
};