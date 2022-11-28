#pragma once

#include "EntityComponentSystem.h"
#include "Vector2D.h"

class Projectile : public Entity
{
public:
	Projectile();
	Projectile(Vector2D position, float projRange, float projSpeed);
	~Projectile();

	virtual void Init();
	virtual void Update();

private:
	Vector2D playerStartPosition;

	class TransformComponent* projectileTransform = nullptr;

	float range = 0;
	float distance = 0;
	float speed = 0;
};