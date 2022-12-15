#pragma once

#include "Projectile.h"
#include "Vector2D.h"

class TransformComponent;

class EnemyProjectile : public Projectile
{
public:
	EnemyProjectile();
	EnemyProjectile(Vector2D position, float projRange, float projSpeed);
	~EnemyProjectile();

	virtual void Init();
	virtual void Update();

private:
	Vector2D projectileStartPosition;

	TransformComponent* projectileTransform = nullptr;

	float range = 0;
	float distance = 0;
	float speed = 0;
};