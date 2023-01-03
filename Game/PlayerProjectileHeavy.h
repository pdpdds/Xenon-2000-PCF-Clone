#pragma once

#include "Projectile.h"
#include "Vector2D.h"

class TransformComponent;

class PlayerProjectileHeavy : public Projectile
{
public:
	PlayerProjectileHeavy();
	PlayerProjectileHeavy(Vector2D position, float projRange, float projSpeed);
	~PlayerProjectileHeavy();

	virtual void Init();
	virtual void Update();
	virtual void BeginOverlap(Entity* otherEntity);
	virtual void EndOverlap(Entity* otherEntity);

private:
	Vector2D projectileStartPosition;

	TransformComponent* projectileTransform = nullptr;

	float range = 0;
	float distance = 0;
	float speed = 0;
};