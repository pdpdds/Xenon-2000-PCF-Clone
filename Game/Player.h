#pragma once

#include "Pawn.h"
#include "Vector2D.h"

class Player : public Pawn
{
public:
	Player();
	~Player();

	virtual void Init();
	virtual void Update();

	virtual void Fire();

private:
	Vector2D playerStartPosition;
	Vector2D playerPosition;
	float playerSpeed;

	class TransformComponent* playerTransform = nullptr;
};