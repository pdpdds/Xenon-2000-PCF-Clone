#pragma once

#include "Pawn.h"

class Enemy : public Pawn
{
public:
	Enemy();
	virtual ~Enemy();

	virtual void Init() = 0;
	virtual void Update() = 0;

	virtual void Fire() = 0;
};