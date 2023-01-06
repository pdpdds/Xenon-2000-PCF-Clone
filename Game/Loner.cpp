#include "Loner.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "GroupLabels.h"
#include "GameManager.h"
#include "EnemyProjectile.h"
#include "ColliderComponent.h"
#include "CollisionComponent.h"
#include "../include/Box2D/box2d/box2d.h"
#include <World.h>

Loner::Loner()
{
	startPosition = Vector2D(1000.f, rand() % 400);
	speed = 0.f;

	fireTimer = 0.f;
	fireTimerMax = 45.f;
	
	this->maxHp = 100;
	this->hp = this->maxHp;
}

Loner::~Loner()
{
	transformComponent = nullptr;
}

void Loner::Init()
{
	__super::Init();

	AddComponent<TransformComponent>(startPosition.x, startPosition.y);
	AddComponent<SpriteComponent>("../Assets/graphics/LonerA.bmp", true, true);
	AddComponent<ColliderComponent>(this, 64, 64);
	//GetComponent<ColliderComponent>().SetCollisionFilter(EntityCategory::ENEMY, 0x0001);
	//AddComponent<CollisionComponent>();
	GetComponent<SpriteComponent>().Play("EnemyIdle");

	SetName("Loner");
	SetTag(Tag::Enemy);

	speed = rand() % (int)3.1f + 3;
	transformComponent = &GetComponent<TransformComponent>();
}

void Loner::Update()
{
	if (IsActive())
	{
		__super::Update();

		transformComponent->velocity.x = -1 * speed;

		Fire();

		if (transformComponent->position.x < -50)
		{
			Destroyed(this);
		}
	}
}

void Loner::Fire()
{
	fireTimer += 0.5;

	if (fireTimer >= fireTimerMax)
	{
		GameManager::GetInstance()->InstantiateProjectile<EnemyProjectile>(
			Vector2D(transformComponent->position.x, transformComponent->position.y), 850, 6);

		fireTimer = 0;
	}
}

void Loner::BeginOverlap(Entity* otherEntity)
{
	if (otherEntity->GetTag() == Tag::Projectile)
	{
		GetComponent<SpriteComponent>().SetFlashing(true);
	}
}

void Loner::EndOverlap(Entity* otherEntity)
{
	if (otherEntity->GetTag() == Tag::Projectile)
	{
		GetComponent<SpriteComponent>().SetFlashing(false);
	}
}

void Loner::TakeDamage(float damage)
{
	this->hp -= damage;
	
	if (this->hp <= 0)
	{
		Destroyed(this);
	}
}
