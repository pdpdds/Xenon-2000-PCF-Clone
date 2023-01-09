#pragma once

#include "Asteroid.h"
#include "Vector2D.h"

class TransformComponent;

class SmallAsteroid : public Asteroid
{
public:
	SmallAsteroid();
	~SmallAsteroid();

	virtual void Init();
	virtual void Update();
	virtual void Break();
	virtual void TakeDamage(float damage);

	virtual void BeginOverlap(Entity* otherEntity);
	virtual void EndOverlap(Entity* otherEntity);

private:
	Vector2D startPosition;
	float speed;

	float hp;
	float maxHP;

	TransformComponent* transformComponent = nullptr;
};