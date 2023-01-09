#include "Companion.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "GroupLabels.h"
#include "Input.h"
#include <iostream>
#include "GameManager.h"
#include "PlayerProjectile.h"
#include <ColliderComponent.h>
#include "Player.h"
#include "PlayerProjectileMedium.h"
#include "PlayerProjectileHeavy.h"
#include "LogOutput.h"

Companion::Companion(Player* parent)
{
	startPosition = Vector2D(470.f, 700.f);
	spaceship = parent;
	spaceship->numOfCompanions++;
	currentMissileAugment = MissileAugment::DEFAULT;

	this->maxHp = 100;
	this->hp = this->maxHp;
}

Companion::~Companion()
{
	spaceship = nullptr;
	transformComponent = nullptr;
	spriteComponent = nullptr;
}

void Companion::Init()
{
	__super::Init();

	if (!spaceship)
	{
		DebugLog(LogMessage::ERROR, "Player is null");
		return;
	}
	else
	{
		DebugLog(LogMessage::WARNING, "Found Player");
	}

	AddComponent<TransformComponent>(startPosition.x, startPosition.y);
	transformComponent = &GetComponent<TransformComponent>();

	AddComponent<SpriteComponent>("../Assets/graphics/cloneA.bmp", false, false);
	spriteComponent = &GetComponent<SpriteComponent>();

	AddComponent<ColliderComponent>(this, 32, 32);

	SetName("Companion");
	SetTag(Tag::Player);

	gunOffset = Vector2D(1, -20);

	if (spaceship->numOfCompanions == 1)
	{
		offsetX = 80.f;
	}
	else if (spaceship->numOfCompanions == 2)
	{
		offsetX = -50.f;
	}
}

void Companion::Update()
{
	__super::Update();

	if (spaceship)
	{
		transformComponent->position.x = spaceship->GetPosition().x + offsetX;
		transformComponent->position.y = spaceship->GetPosition().y + 10.f;
	
		position = transformComponent->position;

		Fire();
	}
	
}

void Companion::Fire()
{
	if (spaceship->IsFiring())
	{
		//GameManager::GetInstance()->InstantiateProjectile<PlayerProjectile>(Vector2D(position.x + gunOffset.x, position.y + gunOffset.y), 850, 10);	

		if (currentMissileAugment == MissileAugment::DEFAULT)
		{
			GameManager::GetInstance()->InstantiateProjectile<PlayerProjectile>(Vector2D(position.x + gunOffset.x, position.y + gunOffset.y), 850, 12);
		}
		else if (currentMissileAugment == MissileAugment::MEDIUM)
		{
			GameManager::GetInstance()->InstantiateProjectile<PlayerProjectileMedium>(Vector2D(position.x + gunOffset.x, position.y + gunOffset.y), 850, 12);
		}
		else if (currentMissileAugment >= MissileAugment::HEAVY)
		{
			GameManager::GetInstance()->InstantiateProjectile<PlayerProjectileHeavy>(Vector2D(position.x + gunOffset.x, position.y + gunOffset.y), 850, 12);
		}
	}
}

void Companion::BeginOverlap(Entity* otherEntity)
{
	if (otherEntity->GetTag() == Tag::Enemy)
	{
		TakeDamage(5.f);
	}

	if (otherEntity->GetTag() == Tag::Asteroid || otherEntity->GetTag() == Tag::EnemyProjectile)
	{
		GetComponent<SpriteComponent>().SetFlashing(true);
	}
}

void Companion::EndOverlap(Entity* otherEntity)
{
	GetComponent<SpriteComponent>().SetFlashing(false);
}

void Companion::UpgradeWeapon(MissileAugment upgrade)
{
	currentMissileAugment = upgrade;
	DebugLog(LogMessage::WARNING, "Upgraded Companion Weapon");
}

void Companion::TakeDamage(float damage)
{
	this->hp -= damage;

	DebugLog(LogMessage::WARNING, "Companion took " + std::to_string(damage) + " damage");
	DebugLog(LogMessage::WARNING, "Companion has " + std::to_string(this->hp) + " health");

	if (this->hp <= 0 || !spaceship->IsAlive())
	{
		DebugLog(LogMessage::WARNING, "Companion died");
		Destroyed(this);
	}
}

void Companion::BoostHealth(float health)
{
	if (this->hp < this->maxHp)
	{
		this->hp += health;
		DebugLog(LogMessage::WARNING, "Companion received " + std::to_string(health) + " health");
	}
	else
	{
		this->hp = this->maxHp;
	}
}
