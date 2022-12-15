#pragma once

#include "EntityComponentSystem.h"

class SpriteComponent;
class TransformComponent;

class Debris : public Entity
{
public:
	Debris(bool isAlive);
	~Debris();

	virtual void Init();
	virtual void Update();

private:
	float scrollingSpeed = 0.f;
	int horizontalMargin = 0.f;
	int verticalMargin = 0.f;
	int whichDebris = 0;

	SpriteComponent* spriteComponent;
	TransformComponent* transformComponent;

	bool isActive;
};