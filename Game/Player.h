#pragma once

#include "Pawn.h"

class Player : public Pawn
{
public:
	Player();

	void Init() override;
};