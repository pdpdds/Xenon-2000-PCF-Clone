#pragma once

#include "Pawn.h"
#include "Vector2D.h"

class TransformComponent;
class SpriteComponent;
class Player;

enum class MissileAugment : int
{
	DEFAULT = 0,
	MEDIUM = 1,
	HEAVY = 2
};

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

	inline MissileAugment GetMissileAugment() { return currentMissileAugment; }

	void UpgradeWeapon(MissileAugment upgrade);

	virtual void TakeDamage(float damage);

	void BoostHealth(float health);

private:
	Vector2D startPosition;
	Vector2D position;

	TransformComponent* transformComponent = nullptr;
	SpriteComponent* spriteComponent = nullptr;
	Player* spaceship = nullptr;

	MissileAugment currentMissileAugment;

	Vector2D gunOffset;

	float offsetX;
};