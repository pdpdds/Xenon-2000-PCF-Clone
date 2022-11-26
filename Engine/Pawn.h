#pragma once

#include "EntityComponentSystem.h"

class Pawn : public Entity
{
public:
	Pawn();
	virtual ~Pawn();
	
	virtual void Init() = 0 ;
	virtual void Update() = 0;

	virtual void Fire() = 0;
};