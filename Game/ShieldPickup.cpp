#include "ShieldPickup.h"
#include "GameManager.h"
#include "Companion.h"
#include "ColliderComponent.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "LogOutput.h"
#include "Player.h"
#include "Loner.h"

ShieldPickup::ShieldPickup()
{
	startPosition = Vector2D(rand() % 950, -30);
	speed = 0.f;
	healthBoost = 5.f;
}

ShieldPickup::~ShieldPickup()
{
}

void ShieldPickup::Init()
{
	__super::Init();

	AddComponent<TransformComponent>(startPosition.x, startPosition.y);
	AddComponent<SpriteComponent>("../Assets/graphics/ShieldPickup.bmp", true, true);
	GetComponent<SpriteComponent>().Play("PickupIdle");
	AddComponent<ColliderComponent>(this, 64, 64);

	SetName("WeaponPickup");
	SetTag(Tag::Pickup);

	speed = 2.5f;
	transformComponent = &GetComponent<TransformComponent>();
}

void ShieldPickup::Update()
{
	__super::Update();

	transformComponent->velocity.y = 1 * speed;

	if (transformComponent->position.y > 850)
	{
		Destroy();
	}
}

void ShieldPickup::BeginOverlap(Entity* otherEntity)
{
	if (otherEntity->GetTag() == Tag::Player)
	{
		Player* player = dynamic_cast<Player*>(otherEntity);
		Companion* companion = dynamic_cast<Companion*>(otherEntity);

		if (player)
		{
			player->BoostHealth(healthBoost);
		}

		if (companion)
		{
			companion->BoostHealth(healthBoost);
		}
		Destroy();
	}
}

void ShieldPickup::EndOverlap(Entity* otherEntity)
{
}
