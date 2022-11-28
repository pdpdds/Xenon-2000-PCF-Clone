#pragma once

#include "EntityComponentSystem.h"

class Debris : public Entity
{
public:
	Debris(bool isLeftDebris);
	~Debris();

	virtual void Init();
	virtual void Update();

private:
	float scrollingSpeed = 0.f;

	class SpriteComponent* spriteComponent;
	class TransformComponent* transformComponent;

	bool leftDebris;
};