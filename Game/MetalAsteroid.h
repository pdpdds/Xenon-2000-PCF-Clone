#pragma once

#include "Asteroid.h"
#include "Vector2D.h"

class TransformComponent;
class SpriteComponent;

class MetalAsteroid : public Asteroid
{
public:
	MetalAsteroid();
	~MetalAsteroid();

	virtual void Init();
	virtual void Update();

	virtual void BeginOverlap(Entity* otherEntity);
	virtual void EndOverlap(Entity* otherEntity);

private:
	Vector2D startPosition;
	float speed;

	TransformComponent* transformComponent = nullptr;
	SpriteComponent* spriteComponent = nullptr;
};