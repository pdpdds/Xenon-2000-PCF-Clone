#pragma once
#include "EntityComponentSystem.h"

class Projectile : public Entity
{
public:
	Projectile();
	~Projectile();

	virtual void Init();
	virtual void Update() override;

	void Spawn(class Vector2D pos, int range, int speed);

private:
	class TransformComponent* projectileTransform;

	int range = 100;
	int speed = 1;
	int distance = 1;
};