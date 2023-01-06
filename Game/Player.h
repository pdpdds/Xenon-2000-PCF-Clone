#pragma once

#include "Pawn.h"
#include "Vector2D.h"

class TransformComponent;
class SpriteComponent;
class Companion;

enum class WeaponAugment : int
{
	DEFAULT = 0,
	MEDIUM = 1,
	HEAVY = 2
};

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

	virtual void TakeDamage(float damage);

	bool CanFire();

	bool IsFiring();

	inline Vector2D GetPosition() { return playerPosition; }

	inline WeaponAugment GetWeaponAugment() { return currentWeaponAugment; }

	inline Companion* GetCompanion() { return playerCompanion; }

	void FireCooldown();

	void UpgradeWeapon(WeaponAugment upgrade);

	void ResetLife();

	bool IsAlive();

private:
	Vector2D playerStartPosition;
	Vector2D playerPosition;
	float playerSpeed;

	TransformComponent* playerTransform = nullptr;
	SpriteComponent* spriteComponent = nullptr;

	float fireTimer;
	float fireTimerMax;

	bool canFire;
	bool isFiring;

	int playerLives;

	WeaponAugment currentWeaponAugment;

	Vector2D gunOffset;

	Companion* playerCompanion;
};