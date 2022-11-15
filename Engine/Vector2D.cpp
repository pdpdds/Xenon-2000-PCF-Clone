#include "Vector2D.h"
#include "MathLibrary.h"

Vector2D::Vector2D()
{
	x = 0.f;
	y = 0.f;
}

Vector2D& Vector2D::Add(const Vector2D& vec)
{
	this->x += vec.x;
	this->y += vec.y;

	return *this;
}

Vector2D& Vector2D::Subtract(const Vector2D& vec)
{
	this->x -= vec.x;
	this->y -= vec.y;

	return *this;
}

Vector2D& Vector2D::Multiply(const Vector2D& vec)
{
	this->x *= vec.x;
	this->y *= vec.y;

	return *this;
}

Vector2D& Vector2D::Divide(const Vector2D& vec)
{
	this->x /= vec.x;
	this->y /= vec.y;

	return *this;
}

Vector2D Vector2D::Interpolate(const Vector2D& vec1, const Vector2D& vec2, float t)
{
	return Vector2D(vec1.x + (vec2.x - vec1.x) * t, vec1.y + (vec2.y - vec1.y) * t);
}

float Vector2D::Length()
{
	return MathLibrary::SquareRoot(x * x + y * y);
}

void Vector2D::Normalize()
{
	float length = Length();

	if (length > 0.f)
	{
		x /= length;
		y /= length;
	}
}

void Vector2D::Clamp(float min_x, float max_x, float min_y, float max_y)
{
	if (x < min_x)
	{
		x = min_x;
	}
	if (x > max_x)
	{
		x = max_x;
	}
	if (y < min_y)
	{
		y = min_y;
	}
	if (y > max_y)
	{
		y = max_y;
	}
}

Vector2D& operator+(Vector2D& vec1, const Vector2D& vec2)
{
	return vec1.Add(vec2);
}

Vector2D& operator-(Vector2D& vec1, const Vector2D& vec2)
{
	return vec1.Subtract(vec2);
}

Vector2D& operator*(Vector2D& vec1, const Vector2D& vec2)
{
	return vec1.Multiply(vec2);
}

Vector2D& operator/(Vector2D& vec1, const Vector2D& vec2)
{
	return vec1.Divide(vec2);
}

std::ostream& operator<<(std::ostream stream, const Vector2D& vec)
{
	stream << "(" << vec.x << "," << vec.y << ")";

	return stream;
}

Vector2D& Vector2D::operator+=(const Vector2D& vec)
{
	return this->Add(vec);
}

Vector2D& Vector2D::operator-=(const Vector2D& vec)
{
	return this->Subtract(vec);
}

Vector2D& Vector2D::operator*=(const Vector2D& vec)
{
	return this->Multiply(vec);
}

Vector2D& Vector2D::operator/=(const Vector2D& vec)
{
	return this->Divide(vec);
}