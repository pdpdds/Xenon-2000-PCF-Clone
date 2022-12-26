#include "Player.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "GroupLabels.h"
#include "Input.h"
#include <iostream>
#include "GameManager.h"
#include "PlayerProjectile.h"
#include <ColliderComponent.h>

Player::Player()
{
	playerStartPosition = Vector2D(470.f, 700.f);
	playerSpeed = 0.f;
	
	fireTimer = 0.f;
	fireTimerMax = 2.5f;
	canFire = true;
	isFiring = false;
}

Player::~Player()
{
	delete playerTransform;
	delete spriteComponent;
}

void Player::Init()
{	
	__super::Init();

	AddComponent<TransformComponent>(playerStartPosition.x, playerStartPosition.y);
	playerTransform = &GetComponent<TransformComponent>();

	AddComponent<SpriteComponent>("../Assets/graphics/Ship.bmp", true, true);
	spriteComponent = &GetComponent<SpriteComponent>();

	spriteComponent->Play("PlayerIdle");

	AddComponent<ColliderComponent>(this, 64, 64);

	playerSpeed = 3.f;

	SetName("Player");


	gunOffset = Vector2D(18, -20);

	std::cout << "Player Initialized" << std::endl;
}

void Player::Update()
{
	__super::Update();

	playerPosition = playerTransform->position;

	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_W) 
		|| Input::GetInstance()->GetButtonDown(SDL_CONTROLLER_BUTTON_DPAD_UP)
		|| Input::GetInstance()->GetAxis(SDL_CONTROLLER_AXIS_LEFTY) < -1)
	{
		playerTransform->velocity.y = -1 * playerSpeed;
	}
	else
	{
		playerTransform->velocity.y = 0;
	}

	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A) 
		|| Input::GetInstance()->GetButtonDown(SDL_CONTROLLER_BUTTON_DPAD_LEFT)
		|| Input::GetInstance()->GetAxis(SDL_CONTROLLER_AXIS_LEFTX) < 0)
	{ 
		spriteComponent->Play("PlayerTurnRight");
		spriteComponent->spriteFlip = SDL_FLIP_HORIZONTAL;
		playerTransform->velocity.x = -1 * playerSpeed;
	}
	else
	{
		spriteComponent->Play("PlayerIdle");
		spriteComponent->spriteFlip = SDL_FLIP_NONE;
		playerTransform->velocity.x = 0;
	}

	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_S) 
		|| Input::GetInstance()->GetButtonDown(SDL_CONTROLLER_BUTTON_DPAD_DOWN)
		|| Input::GetInstance()->GetAxis(SDL_CONTROLLER_AXIS_LEFTY) > 0)
	{
		playerTransform->velocity.y = 1 * playerSpeed;
	}

	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D) 
		|| Input::GetInstance()->GetButtonDown(SDL_CONTROLLER_BUTTON_DPAD_RIGHT)
		|| Input::GetInstance()->GetAxis(SDL_CONTROLLER_AXIS_LEFTX) > 0)
	{
		spriteComponent->Play("PlayerTurnRight");
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
		isFiring = true;
		GameManager::GetInstance()->InstantiateProjectile<PlayerProjectile>(Vector2D(playerPosition.x + gunOffset.x, playerPosition.y + gunOffset.y), 850, 10);
	}	
	else
	{
		isFiring = false;
	}
}

void Player::BeginOverlap(Entity* otherEntity)
{
}

void Player::EndOverlap(Entity* otherEntity)
{
}

bool Player::CanFire()
{
	return canFire;
}

bool Player::IsFiring()
{
	return isFiring;
}

void Player::FireCooldown()
{
	canFire = false;
	//isFiring = false;

	fireTimer += 0.3f;

	if (fireTimer >= fireTimerMax)
	{
		canFire = true;
		fireTimer = 0.f;
	}
}
