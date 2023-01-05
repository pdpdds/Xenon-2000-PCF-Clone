#pragma once

#include "Pawn.h"
#include "Vector2D.h"

class TransformComponent;
class SpriteComponent;
class Player;

class Companion : public Pawn
{
public:
	Companion(Player* parent);
	~Companion();

	virtual void Init();
	virtual void Update();

	virtual void Fire();

	virtual void BeginOverlap(Entity* otherEntity);
	virtual void EndOverlap(Entity* otherEntity);

	//bool CanFire();

	/*void FireCooldown();*/

	virtual void TakeDamage(float damage);

private:
	Vector2D startPosition;
	Vector2D position;

	TransformComponent* transformComponent = nullptr;
	SpriteComponent* spriteComponent = nullptr;
	Player* spaceship = nullptr;

	Vector2D gunOffset;
};