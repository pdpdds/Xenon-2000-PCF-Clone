#pragma once

#include "EntityComponentSystem.h"

class Pickup : public Entity
{
public:
	Pickup();
	virtual ~Pickup();

	virtual void Init() = 0;
	virtual void Update() = 0;
};