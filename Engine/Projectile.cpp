#include "Projectile.h"
#include "Vector2D.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include <iostream>

Projectile::Projectile(Vector2D position, float projRange, float projSpeed)
{
	range = projRange;
	speed = projSpeed;
	playerStartPosition = position;
}

Projectile::~Projectile()
{
	Destroy();
	delete projectileTransform;
}

void Projectile::Init()
{
	__super::Init();

	AddComponent<TransformComponent>(playerStartPosition.x, playerStartPosition.y);
	AddComponent<SpriteComponent>("../Assets/graphics/missileA.bmp", false);
	projectileTransform = &GetComponent<TransformComponent>();
}

void Projectile::Update()
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
