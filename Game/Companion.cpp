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

Companion::Companion(Player* parent)
{
	startPosition = Vector2D(470.f, 700.f);
	spaceship = parent;

	//fireTimer = 0.f;
	//fireTimerMax = 2.5f;
	//canFire = true;
}

Companion::~Companion()
{
	delete transformComponent;
	delete spriteComponent;
}

void Companion::Init()
{
	__super::Init();

	AddComponent<TransformComponent>(startPosition.x, startPosition.y);
	transformComponent = &GetComponent<TransformComponent>();

	AddComponent<SpriteComponent>("../Assets/graphics/cloneA.bmp", false, false);
	spriteComponent = &GetComponent<SpriteComponent>();

	AddComponent<ColliderComponent>(this, 32, 32);

	SetName("Companion");

	if (spaceship->IsActive())
	{
		std::cout << "Companion found spaceship: " << spaceship->GetName() << std::endl;
	}


	gunOffset = Vector2D(1, -20);
}

void Companion::Update()
{
	__super::Update();

	if (spaceship->IsActive())
	{
		transformComponent->position.x = spaceship->GetPosition().x + 80.f;
		transformComponent->position.y = spaceship->GetPosition().y + 10.f;

		position = transformComponent->position;

		Fire();
		/*FireCooldown();*/
	}
	
}

void Companion::Fire()
{
	if (spaceship->IsFiring())
	{
		GameManager::GetInstance()->InstantiateProjectile<PlayerProjectile>(Vector2D(position.x + gunOffset.x, position.y + gunOffset.y), 850, 10);
	}
}

void Companion::BeginOverlap(Entity* otherEntity)
{
}

void Companion::EndOverlap(Entity* otherEntity)
{
}

//bool Companion::CanFire()
//{
//	return canFire;
//}
//
//void Companion::FireCooldown()
//{
//	canFire = false;
//
//	fireTimer += 0.3f;
//
//	if (fireTimer >= fireTimerMax)
//	{
//		canFire = true;
//		fireTimer = 0.f;
//	}
//}
