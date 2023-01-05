#include "Pawn.h"
#include "GameEngine.h"
#include <iostream>
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "PlayerController.h"
#include "Vector2D.h"
#include "GroupLabels.h"

Pawn::Pawn()
{
	maxHp = 0.f;
	hp = maxHp;
}

Pawn::~Pawn()
{

}

void Pawn::Init()
{
	__super::Init();
}

void Pawn::Update()
{
	__super::Update();
}
