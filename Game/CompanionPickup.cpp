#include "CompanionPickup.h"
#include "GameManager.h"
#include "Companion.h"
#include "ColliderComponent.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "LogOutput.h"
#include "Player.h"
#include "Loner.h"

CompanionPickup::CompanionPickup()
{
	startPosition = Vector2D(rand() % 950, -10);
	speed = 0.f;
}

CompanionPickup::~CompanionPickup()
{
}

void CompanionPickup::Init()
{
	__super::Init();

	AddComponent<TransformComponent>(startPosition.x, startPosition.y);
	AddComponent<SpriteComponent>("../Assets/graphics/cloneA.bmp", false, false);
	AddComponent<ColliderComponent>(this, 64, 64);

	SetName("CompanionPickup");
	SetTag(Tag::Pickup);

	speed = 2.5f;
	transformComponent = &GetComponent<TransformComponent>();
}

void CompanionPickup::Update()
{
	__super::Update();

	
	transformComponent->velocity.y = 1 * speed;


	if (transformComponent->position.y > 850)
	{
		Destroy();
	}
}

void CompanionPickup::BeginOverlap(Entity* otherEntity)
{
	if (otherEntity->GetTag() == Tag::Player)
	{
		Player* player = dynamic_cast<Player*>(otherEntity);

		if (player)
		{
			//DebugLog(LogMessage::LOG, "Picked up Companion");
			//GameManager::GetManager()->CreateEntity<Companion>(player);
			Destroy();
		}
	}
}

void CompanionPickup::EndOverlap(Entity* otherEntity)
{
}
