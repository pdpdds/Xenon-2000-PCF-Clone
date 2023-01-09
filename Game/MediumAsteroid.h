#pragma once

#include "Asteroid.h"
#include "Vector2D.h"

class TransformComponent;
class SpriteComponent;

class MediumAsteroid : public Asteroid
{
public:
	MediumAsteroid();
	~MediumAsteroid();

	virtual void Init();
	virtual void Update();
	virtual void Break();
	virtual void TakeDamage(float damage);

	virtual void BeginOverlap(Entity* otherEntity);
	virtual void EndOverlap(Entity* otherEntity);

	void CreateNewAsteroids();

private:
	Vector2D startPosition;
	float speed;

	float hp;
	float maxHP;

	TransformComponent* transformComponent = nullptr;
	SpriteComponent* spriteComponent = nullptr;
};