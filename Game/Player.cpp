#include "Player.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "Input.h"
#include "GameManager.h"
#include "PlayerProjectile.h"
#include "ColliderComponent.h"
#include "PlayerProjectileMedium.h"
#include "PlayerProjectileHeavy.h"
#include "LogOutput.h"
#include "Companion.h"

Player::Player()
{
	playerStartPosition = Vector2D(470.f, 700.f);
	playerSpeed = 0.f;
	currentWeaponAugment = WeaponAugment::DEFAULT;
	
	fireTimer = 0.f;
	fireTimerMax = 2.5f;
	canFire = true;
	isFiring = false;

	this->maxHp = 100.f;
	this->hp = maxHp;

	playerLives = 3;
}

Player::~Player()
{
	playerTransform = nullptr;
	spriteComponent = nullptr;
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

	SetTag(Tag::Player);

	gunOffset = Vector2D(18, -20);

	 playerCompanion = GameManager::GetManager()->CreateEntity<Companion>(this);

	std::cout << "Player Initialized" << std::endl;
	std::cout << "Player lives: " << playerLives << std::endl;
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
		if (currentWeaponAugment == WeaponAugment::DEFAULT)
		{
			isFiring = true;
			GameManager::GetInstance()->InstantiateProjectile<PlayerProjectile>(Vector2D(playerPosition.x + gunOffset.x, playerPosition.y + gunOffset.y * 2), 850, 10);
		}
		else if (currentWeaponAugment == WeaponAugment::MEDIUM)
		{
			isFiring = true;
			GameManager::GetInstance()->InstantiateProjectile<PlayerProjectileMedium>(Vector2D(playerPosition.x + gunOffset.x, playerPosition.y + gunOffset.y), 850, 10);
		}
		else if (currentWeaponAugment >= WeaponAugment::HEAVY)
		{
			isFiring = true;
			GameManager::GetInstance()->InstantiateProjectile<PlayerProjectileHeavy>(Vector2D(playerPosition.x + gunOffset.x, playerPosition.y + gunOffset.y * 2), 850, 10);
		}
	}	
	else
	{
		isFiring = false;
	}
}

void Player::BeginOverlap(Entity* otherEntity)
{
	if (otherEntity->GetTag() == Tag::Enemy)
	{
		TakeDamage(5.f);
	}
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

void Player::UpgradeWeapon(WeaponAugment upgrade)
{
	currentWeaponAugment = upgrade;
	DebugLog(LogMessage::WARNING, "Upgraded Player Weapon");
}

void Player::ResetLife()
{
	this->hp = this->maxHp;
	DebugLog(LogMessage::WARNING, "Player Lives: " + std::to_string(playerLives));

	//std::cout << "Player lives: " << playerLives << std::endl;
}

void Player::TakeDamage(float damage)
{
	this->hp -= damage;

	DebugLog(LogMessage::WARNING, "Player took " + std::to_string(damage) + " damage");
	DebugLog(LogMessage::WARNING, "Player has " + std::to_string(this->hp) + " health");
	/*std::cout << "Player took " << damage << " damage" << std::endl;
	std::cout << "Player has " << this->hp << " health" << std::endl;*/

	if (this->hp <= 0)
	{
		if (playerLives > 0)
		{
			playerLives--;
			ResetLife();
		}
		else if (playerLives <= 0)
		{
			playerLives = 0;
			DebugLog(LogMessage::WARNING, "Player died");
			Destroy();
		}
	}
}

bool Player::IsAlive()
{
	if (this->hp <= 0)
	{
		return true;
	}
	return false;
}
