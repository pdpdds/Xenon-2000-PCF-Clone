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
	
}

Pawn::~Pawn()
{
	Destroy();
}

void Pawn::Init()
{
	__super::Init();
}

void Pawn::Update()
{
	__super::Update();
}
