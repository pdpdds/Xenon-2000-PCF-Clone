#include "EnemyProjectile.h"
#include "Vector2D.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include <iostream>
#include <ColliderComponent.h>

EnemyProjectile::EnemyProjectile()
{
}

EnemyProjectile::EnemyProjectile(Vector2D position, float projRange, float projSpeed)
{
	projectileStartPosition = position;
	range = projRange;
	speed = projSpeed;

	this->projectileDamage = 10.f;
}

EnemyProjectile::~EnemyProjectile()
{
	projectileTransform = nullptr;
}

void EnemyProjectile::Init()
{
	__super::Init();

	AddComponent<TransformComponent>(projectileStartPosition.x, projectileStartPosition.y);
	AddComponent<SpriteComponent>("../Assets/graphics/EnemyWeap6.bmp", false, false);
	AddComponent<ColliderComponent>(this, 64, 64);
	projectileTransform = &GetComponent<TransformComponent>();

	SetTag(Tag::EnemyProjectile);
	SetName("Enemy Projectile");
}

void EnemyProjectile::Update()
{
	__super::Update();

	distance += speed;

	projectileTransform->velocity.y = 1 * speed;

	//If the distance traveled is greater than the projectile range, destroy the projectile
	if (distance > range)
	{
		Destroy();
	}
}

void EnemyProjectile::BeginOverlap(Entity* otherEntity)
{
	if (otherEntity->GetTag() == Tag::Player)
	{
		otherEntity->TakeDamage(this->projectileDamage);
	}

	if (otherEntity->GetTag() == Tag::Projectile)
	{
		Destroyed(this);
	}
}

void EnemyProjectile::EndOverlap(Entity* otherEntity)
{
}
