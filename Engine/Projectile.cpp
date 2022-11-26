#include "Projectile.h"
#include "Vector2D.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "ProjectileComponent.h"
#include <iostream>

Projectile::Projectile()
{
	/*range = projectileRange;
	speed = projectileSpeed;*/
	/*Spawn(position, range, speed);*/
}

Projectile::~Projectile()
{
	Destroy();
}

void Projectile::Init()
{
	std::cout << "Projectile Initialized" << std::endl;
	projectileTransform = &GetComponent<TransformComponent>();
}

void Projectile::Update()
{
	distance += speed;

	GetComponent<TransformComponent>().velocity.y = -1 * speed;

	//If the distance traveled is greater than the projectile range, destroy the projectile
	if (distance >= range)
	{
		Destroy();
	}
}

void Projectile::Spawn(Vector2D pos, int range, int speed)
{
	AddComponent<TransformComponent>(pos.x, pos.y);
	AddComponent<SpriteComponent>("../Assets/graphics/playerjet.bmp", false);
}
