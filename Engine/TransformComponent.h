#pragma once

#include "Components.h"
#include "Vector2D.h"

class TransformComponent : public Component
{
public:
	TransformComponent()
	{
		position.SetX(0.f);
		position.SetY(0.f);
	}
	TransformComponent(float x, float y)
	{
		position.SetX(x);
		position.SetY(y);
	}

	~TransformComponent()
	{

	}

	void Init() override
	{
		velocity.SetX(0.f);
		velocity.SetY(0.f);
	}

	void Update() override
	{
		position.x += velocity.x;
		position.y += velocity.y;
	}

	inline Vector2D GetPosition() const { return position; }

	Vector2D position;
	Vector2D velocity;

	int speed = 3;
	int width = TILESIZE;
	int height = TILESIZE;
	int scale = 1;

};