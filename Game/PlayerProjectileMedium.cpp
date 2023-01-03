#include "PlayerProjectileMedium.h"
#include "Vector2D.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "ColliderComponent.h"
#include <iostream>

PlayerProjectileMedium::PlayerProjectileMedium()
{
}

PlayerProjectileMedium::PlayerProjectileMedium(Vector2D position, float projRange, float projSpeed)
{
	projectileStartPosition = position;
	range = projRange;
	speed = projSpeed;
}

PlayerProjectileMedium::~PlayerProjectileMedium()
{
}

void PlayerProjectileMedium::Init()
{
	__super::Init();

	AddComponent<TransformComponent>(projectileStartPosition.x, projectileStartPosition.y);
	AddComponent<SpriteComponent>("../Assets/graphics/missileB.bmp", false, false);
	AddComponent<ColliderComponent>(this, 64, 64);
	projectileTransform = &GetComponent<TransformComponent>();

	SetName("PlayerBulletMedium");
	SetTag(Tag::Projectile);
}

void PlayerProjectileMedium::Update()
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

void PlayerProjectileMedium::BeginOverlap(Entity* otherEntity)
{
	if (otherEntity->GetTag() == Tag::Enemy)
	{
		std::cout << "Player bullet" << " colliding with " << otherEntity->GetName() << std::endl;
	}
}

void PlayerProjectileMedium::EndOverlap(Entity* otherEntity)
{

}
