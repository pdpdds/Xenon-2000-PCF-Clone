#include "Player.h"
#include "GameEngine.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "PlayerController.h"
#include "Vector2D.h"
#include "GroupLabels.h"
#include <iostream>

Player::Player()
{
	
}

void Player::Init()
{	
	__super::Init();
	
	std::cout << "Player Initialized" << std::endl;
	this->AddComponent<TransformComponent>(50.f, 50.f);
	this->AddComponent<SpriteComponent>("../Assets/graphics/ShipIdle.bmp", false);
}

void Player::Update()
{
	__super::Update();
}
