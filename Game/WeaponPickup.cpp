#include "WeaponPickup.h"
#include "GameManager.h"
#include "Companion.h"
#include "ColliderComponent.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "LogOutput.h"
#include "Player.h"
#include "Loner.h"

const WeaponAugment weaponUpgrades[] = { WeaponAugment::DEFAULT, WeaponAugment::MEDIUM, WeaponAugment::HEAVY };
const MissileAugment missileUpgrades[] = { MissileAugment::DEFAULT, MissileAugment::MEDIUM, MissileAugment::HEAVY };

WeaponPickup::WeaponPickup()
{
	startPosition = Vector2D(rand() % 950, -30);
	speed = 0.f;
}

WeaponPickup::~WeaponPickup()
{
}

void WeaponPickup::Init()
{
	__super::Init();

	AddComponent<TransformComponent>(startPosition.x, startPosition.y);
	AddComponent<SpriteComponent>("../Assets/graphics/WeaponPickup.bmp", true, true);
	GetComponent<SpriteComponent>().Play("PickupIdle");
	AddComponent<ColliderComponent>(this, 64, 64);

	SetName("WeaponPickup");
	SetTag(Tag::Pickup);

	speed = 2.5f;
	transformComponent = &GetComponent<TransformComponent>();
}

void WeaponPickup::Update()
{
	__super::Update();

	transformComponent->velocity.y = 1 * speed;

	if (transformComponent->position.y > 850)
	{
		Destroy();
	}
}

void WeaponPickup::BeginOverlap(Entity* otherEntity)
{
	if (otherEntity->GetTag() == Tag::Player)
	{
		Player* player = dynamic_cast<Player*>(otherEntity);
		Companion* companion = dynamic_cast<Companion*>(otherEntity);

		if (player)
		{
			int currentUpgrade = static_cast<int>(player->GetWeaponAugment());
			int nextUpgrade = (currentUpgrade + 1) % (sizeof(weaponUpgrades) / sizeof(weaponUpgrades[0]));

			if (currentUpgrade < 2)
			{
				player->UpgradeWeapon(weaponUpgrades[nextUpgrade]);
			}
			else
			{
				Destroy();
			}
			
		}

		if (companion)
		{
			int currentUpgrade = static_cast<int>(companion->GetMissileAugment());
			int nextUpgrade = (currentUpgrade + 1) % (sizeof(missileUpgrades) / sizeof(missileUpgrades[0]));

			if (currentUpgrade < 2)
			{
				companion->UpgradeWeapon(missileUpgrades[nextUpgrade]);
			}
			else
			{
				Destroy();
			}
		}

		Destroy();
	}
}

void WeaponPickup::EndOverlap(Entity* otherEntity)
{
}
