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
}

EnemyProjectile::~EnemyProjectile()
{
}

void EnemyProjectile::Init()
{
	__super::Init();

	AddComponent<TransformComponent>(projectileStartPosition.x, projectileStartPosition.y);
	AddComponent<SpriteComponent>("../Assets/graphics/EnemyWeap6.bmp", false, false);
	AddComponent<ColliderComponent>(this, 32, 32);
	projectileTransform = &GetComponent<TransformComponent>();
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
}
