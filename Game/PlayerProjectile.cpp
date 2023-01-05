#include "PlayerProjectile.h"
#include "Vector2D.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "ColliderComponent.h"
#include <iostream>

PlayerProjectile::PlayerProjectile()
{
}

PlayerProjectile::PlayerProjectile(Vector2D position, float projRange, float projSpeed)
{
	projectileStartPosition = position;
	range = projRange;
	speed = projSpeed;
	this->projectileDamage = 10.f;
}

PlayerProjectile::~PlayerProjectile()
{
}

void PlayerProjectile::Init()
{
	__super::Init();
	
	AddComponent<TransformComponent>(projectileStartPosition.x, projectileStartPosition.y);
	AddComponent<SpriteComponent>("../Assets/graphics/missileA.bmp", false, false);
	AddComponent<ColliderComponent>(this, 32, 32);
	projectileTransform = &GetComponent<TransformComponent>();

	SetName("PlayerBullet");
	SetTag(Tag::Projectile);
}

void PlayerProjectile::Update()
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

void PlayerProjectile::BeginOverlap(Entity* otherEntity)
{
	if (otherEntity->GetTag() == Tag::Enemy)
	{
		otherEntity->TakeDamage(this->projectileDamage);
	}
}

void PlayerProjectile::EndOverlap(Entity* otherEntity)
{
	
}
