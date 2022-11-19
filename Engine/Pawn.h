#pragma once

#include "GameObjects.h"

class Pawn : public GameObject
{
public:
	Pawn();
	
	void Start() override;
	void Update() override {};

};