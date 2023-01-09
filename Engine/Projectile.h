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

	virtual void Destroyed(Entity* entity);

	float projectileDamage;
};