#pragma once

#include "Pawn.h"
#include "Vector2D.h"

class TransformComponent;
class SpriteComponent;

class Player : public Pawn
{
public:
	Player();
	~Player();

	virtual void Init();
	virtual void Update();

	virtual void Fire();

	virtual void BeginOverlap(Entity* otherEntity);
	virtual void EndOverlap(Entity* otherEntity);

	bool CanFire();

	void FireCooldown();

private:
	Vector2D playerStartPosition;
	Vector2D playerPosition;
	float playerSpeed;

	TransformComponent* playerTransform = nullptr;
	SpriteComponent* spriteComponent = nullptr;

	float fireTimer;
	float fireTimerMax;

	bool canFire;

	float gunOffset;
};