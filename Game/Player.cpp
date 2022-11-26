#include "Player.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "GroupLabels.h"
#include "Input.h"
#include "LevelManager.h"
#include <iostream>

Player::Player()
{
	playerStartPosition = Vector2D(470.f, 700.f);
	playerSpeed = 0.f;
}

void Player::Init()
{	
	__super::Init();

	AddComponent<TransformComponent>(playerStartPosition.x, playerStartPosition.y);
	AddComponent<SpriteComponent>("../Assets/graphics/ShipIdle.bmp", false);

	playerSpeed = 3.f;
	playerTransform = &GetComponent<TransformComponent>();

	std::cout << "Player Initialized" << std::endl;
}

void Player::Update()
{
	__super::Update();

	playerPosition = playerTransform->position;

	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_W))
	{
		GetComponent<TransformComponent>().velocity.y = -1 * playerSpeed;
	}
	else
	{
		GetComponent<TransformComponent>().velocity.y = 0;
	}

	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A))
	{
		GetComponent<TransformComponent>().velocity.x = -1 * playerSpeed;
	}
	else
	{
		GetComponent<TransformComponent>().velocity.x = 0;
	}

	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_S))
	{
		GetComponent<TransformComponent>().velocity.y = 1 * playerSpeed;
	}

	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D))
	{
		GetComponent<TransformComponent>().velocity.x = 1 * playerSpeed;
	}

	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_SPACE))
	{
		Fire();
	}
}

void Player::Fire()
{
	//LevelManager::GetInstance()->CreateProjectile(playerPosition, 100, 1);
}
