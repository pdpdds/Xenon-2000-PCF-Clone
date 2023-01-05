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

	bool IsFiring();

	inline Vector2D GetPosition() { return playerPosition; }

	inline int GetWeaponAugment() { return weaponAugment; }

	void FireCooldown();

	void UpgradeWeapon();

	virtual void TakeDamage(float damage);

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

	int weaponAugment;

	Vector2D gunOffset;
};