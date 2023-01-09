#include "PlayerProjectileHeavy.h"
#include "Vector2D.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "ColliderComponent.h"
#include <iostream>
#include "GameManager.h"
#include "MetalAsteroid.h"

PlayerProjectileHeavy::PlayerProjectileHeavy()
{
}

PlayerProjectileHeavy::PlayerProjectileHeavy(Vector2D position, float projRange, float projSpeed)
{
	projectileStartPosition = position;
	range = projRange;
	speed = projSpeed;

	this->projectileDamage = 25.f;
}

PlayerProjectileHeavy::~PlayerProjectileHeavy()
{
}

void PlayerProjectileHeavy::Init()
{
	__super::Init();

	AddComponent<TransformComponent>(projectileStartPosition.x, projectileStartPosition.y);
	AddComponent<SpriteComponent>("../Assets/graphics/missileC.bmp", false, false);
	AddComponent<ColliderComponent>(this, 64, 64);
	projectileTransform = &GetComponent<TransformComponent>();

	SetName("PlayerBulletHeavy");
	SetTag(Tag::Projectile);
}

void PlayerProjectileHeavy::Update()
{
	__super::Update();

	distance += speed;

	projectileTransform->velocity.y = -1 * speed;

	//If the distance traveled is greater than the projectile range, destroy the projectile
	if (distance > range)
	{
		Destroy();
	}
}

void PlayerProjectileHeavy::BeginOverlap(Entity* otherEntity)
{
	if (otherEntity->GetTag() == Tag::Enemy)
	{
		otherEntity->TakeDamage(this->projectileDamage);

		Destroy();
	}

	if (otherEntity->GetTag() == Tag::Asteroid)
	{
		MetalAsteroid* metalAsteroid = dynamic_cast<MetalAsteroid*>(otherEntity);

		if (metalAsteroid)
		{
			Destroyed(this);
		}

		otherEntity->TakeDamage(this->projectileDamage);

		Destroy();
	}
}

void PlayerProjectileHeavy::EndOverlap(Entity* otherEntity)
{
	
}
