#include "PlayerProjectile.h"
#include "Vector2D.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include <iostream>

PlayerProjectile::PlayerProjectile()
{
}

PlayerProjectile::PlayerProjectile(Vector2D position, float projRange, float projSpeed)
{
	projectileStartPosition = position;
	range = projRange;
	speed = projSpeed;
}

PlayerProjectile::~PlayerProjectile()
{
}

void PlayerProjectile::Init()
{
	__super::Init();
	
	AddComponent<TransformComponent>(projectileStartPosition.x, projectileStartPosition.y);
	AddComponent<SpriteComponent>("../Assets/graphics/missileA.bmp", false, false);
	projectileTransform = &GetComponent<TransformComponent>();
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
