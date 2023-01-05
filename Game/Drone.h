#pragma once

#include "Enemy.h"
#include "Vector2D.h"

class TransformComponent;

class Drone : public Enemy
{
public:
	Drone();
	~Drone();

	virtual void Init();
	virtual void Update();

	virtual void Fire();

	virtual void BeginOverlap(Entity* otherEntity);
	virtual void EndOverlap(Entity* otherEntity);

	virtual void TakeDamage(float damage);

private:
	Vector2D startPosition;
	Vector2D playerPosition;
	float speed;

	float amplitude = 50.f;

	TransformComponent* transformComponent = nullptr;
};