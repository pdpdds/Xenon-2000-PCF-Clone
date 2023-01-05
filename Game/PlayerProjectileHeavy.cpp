#include "PlayerProjectileHeavy.h"
#include "Vector2D.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "ColliderComponent.h"
#include <iostream>

PlayerProjectileHeavy::PlayerProjectileHeavy()
{
}

PlayerProjectileHeavy::PlayerProjectileHeavy(Vector2D position, float projRange, float projSpeed)
{
	projectileStartPosition = position;
	range = projRange;
	speed = projSpeed;

	this->projectileDamage = 20.f;
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
	}
}

void PlayerProjectileHeavy::EndOverlap(Entity* otherEntity)
{

}
