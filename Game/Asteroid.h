#pragma once
#include "EntityComponentSystem.h"

class Asteroid : public Entity
{
public:
	Asteroid();
	virtual ~Asteroid();

	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Break();
	virtual void Destroyed(Entity* entity);
};