#pragma once

#include "EntityComponentSystem.h"

class Pawn : public Entity
{
public:
	Pawn();
	
	void Init() override;
	void Update() override {};

};