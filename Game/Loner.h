#pragma once

#include "Pawn.h"
#include "Vector2D.h"

class Loner : public Pawn
{
public:
	Loner();

	virtual void Init();
	virtual void Update();

	virtual void Fire();

private:
	Vector2D playerStartPosition;
	Vector2D playerPosition;
	float playerSpeed;

	class TransformComponent* playerTransform = nullptr;
};