#include "Player.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "GroupLabels.h"
#include "Input.h"
#include <iostream>
#include "LevelManager.h"

Player::Player()
{
	playerStartPosition = Vector2D(470.f, 700.f);
	playerSpeed = 0.f;
	
	fireTimer = 0.f;
	fireTimerMax = 2.5f;
	canFire = true;
}

Player::~Player()
{
	delete playerTransform;
}

void Player::Init()
{	
	__super::Init();

	AddComponent<TransformComponent>(playerStartPosition.x, playerStartPosition.y);
	AddComponent<SpriteComponent>("../Assets/graphics/ShipIdle.bmp", false);

	playerSpeed = 3.f;
	playerTransform = &GetComponent<TransformComponent>();

	gunOffset = playerPosition.x + 15;

	std::cout << "Player Initialized" << std::endl;
}

void Player::Update()
{
	__super::Update();

	playerPosition = playerTransform->position;

	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_W) || Input::GetInstance()->GetButtonDown(SDL_CONTROLLER_BUTTON_DPAD_UP))
	{
		playerTransform->velocity.y = -1 * playerSpeed;
	}
	else
	{
		playerTransform->velocity.y = 0;
	}

	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A) || Input::GetInstance()->GetButtonDown(SDL_CONTROLLER_BUTTON_DPAD_LEFT))
	{
		playerTransform->velocity.x = -1 * playerSpeed;
	}
	else
	{
		playerTransform->velocity.x = 0;
	}

	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_S) || Input::GetInstance()->GetButtonDown(SDL_CONTROLLER_BUTTON_DPAD_RIGHT))
	{
		playerTransform->velocity.y = 1 * playerSpeed;
	}

	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D) || Input::GetInstance()->GetButtonDown(SDL_CONTROLLER_BUTTON_DPAD_DOWN))
	{
		playerTransform->velocity.x = 1 * playerSpeed;
	}

	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_SPACE) || Input::GetInstance()->GetButtonDown(SDL_CONTROLLER_BUTTON_A))
	{
		Fire();
		FireCooldown();
	}
}

void Player::Fire()
{
	if (CanFire())
	{
		LevelManager::GetInstance()->CreateProjectile(Vector2D(playerPosition.x + gunOffset, playerPosition.y), 850, 10);
	}	
}

bool Player::CanFire()
{
	return canFire;
}

void Player::FireCooldown()
{
	canFire = false;

	fireTimer += 0.3f;

	if (fireTimer >= fireTimerMax)
	{
		canFire = true;
		fireTimer = 0.f;
	}
}
