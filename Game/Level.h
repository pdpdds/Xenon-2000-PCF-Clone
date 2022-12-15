#pragma once

#include "EntityComponentSystem.h"

class SpriteComponent;
class TransformComponent;

class Level : public Entity
{
public:
	Level();
	~Level();

	virtual void Init();
	virtual void Update();

private:
	float scrollingSpeed = 0.f;

	SpriteComponent* spriteComponent;
	TransformComponent* transformComponent;
};