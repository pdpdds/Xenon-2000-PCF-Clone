#pragma once

#include "Pawn.h"

class Player : public Pawn
{
public:
	Player();

	virtual void Init();
	virtual void Update();
};