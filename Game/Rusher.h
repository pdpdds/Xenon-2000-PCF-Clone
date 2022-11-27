#pragma once

#include "Pawn.h"
#include "Vector2D.h"

class Rusher : public Pawn
{
public:
	Rusher();
	~Rusher();

	virtual void Init();
	virtual void Update();

	virtual void Fire();

private:
	Vector2D startPosition;
	Vector2D playerPosition;
	float speed;

	class TransformComponent* transformComponent = nullptr;
};