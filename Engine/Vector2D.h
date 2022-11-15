#pragma once

#include <iostream>

class Vector2D
{
public:
	Vector2D();
	Vector2D(float xx, float yy) : x(xx), y(yy) {}

	Vector2D& Add(const Vector2D& vec);
	Vector2D& Subtract(const Vector2D& vec);
	Vector2D& Multiply(const Vector2D& vec);
	Vector2D& Divide(const Vector2D& vec);
	Vector2D Interpolate(const Vector2D& vec1, const Vector2D& vec2, float t);

	friend Vector2D& operator+(Vector2D& vec1, const Vector2D& vec2);
	friend Vector2D& operator-(Vector2D& vec1, const Vector2D& vec2);
	friend Vector2D& operator*(Vector2D& vec1, const Vector2D& vec2);
	friend Vector2D& operator/(Vector2D& vec1, const Vector2D& vec2);

	Vector2D& operator+=(const Vector2D& vec);
	Vector2D& operator-=(const Vector2D& vec);
	Vector2D& operator*=(const Vector2D& vec);
	Vector2D& operator/=(const Vector2D& vec);

	friend std::ostream& operator<<(std::ostream stream, const Vector2D& vec);

	float Length();
	void Normalize();
	
	void Clamp(float min_x, float max_x, float min_y, float max_y);

	//Getters & Setters
	inline float X() const { return x; }
	inline float Y() const { return y; }

	inline void SetX(float xx) { x = xx; }
	inline void SetY(float yy) { y = yy; }

	float x;
	float y;
};