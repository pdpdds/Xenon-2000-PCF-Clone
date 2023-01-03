#include "PlayerProjectile.h"
#include "Vector2D.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "ColliderComponent.h"
#include <iostream>
#include "Loner.h"
#include "Player.h"
#include "Companion.h"

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
	AddComponent<ColliderComponent>(this, 64, 64);
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

	/*std::cout << "Bullet Position: (" << projectileTransform->position.x << " , " << projectileTransform->position.y << ")" << std::endl;
	std::cout << "Bullet Body Position: (" << GetComponent<ColliderComponent>().m_bodyX << " , " << GetComponent<ColliderComponent>().m_bodyY << ")" << std::endl;*/
}

void PlayerProjectile::BeginOverlap(Entity* otherEntity)
{
	if (otherEntity->GetTag() == Tag::Enemy)
	{
		std::cout << "Player bullet" << " colliding with " << otherEntity->GetName() << std::endl;
	}
}

void PlayerProjectile::EndOverlap(Entity* otherEntity)
{
	
}
