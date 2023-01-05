#include "Projectile.h"
#include "Vector2D.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include <iostream>

Projectile::Projectile()
{
	projectileDamage = 0.f;
}

Projectile::Projectile(Vector2D position, float projRange, float projSpeed)
{
	projectileDamage = 0.f;
}

Projectile::~Projectile()
{
	
}

void Projectile::Init()
{
	__super::Init();
}

void Projectile::Update()
{
	__super::Update();
}
