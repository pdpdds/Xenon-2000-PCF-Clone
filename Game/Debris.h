#pragma once

#include "EntityComponentSystem.h"

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

	class SpriteComponent* spriteComponent;
	class TransformComponent* transformComponent;

	bool isActive;
};