#include "Drone.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "GroupLabels.h"
#include "GameManager.h"
#include "EnemyProjectile.h"
#include <ColliderComponent.h>

Drone::Drone()
{
	startPosition = Vector2D(500, 0);
	speed = 0.f;
}

Drone::~Drone()
{

}

void Drone::Init()
{
	__super::Init();

	AddComponent<TransformComponent>(startPosition.x, startPosition.y);
	AddComponent<SpriteComponent>("../Assets/graphics/droneA.bmp", false, false);
	AddComponent<ColliderComponent>(this, 64, 64);
	//GetComponent<ColliderComponent>().SetCollisionFilter(EntityCategory::ENEMY, 0x0001);
	GetComponent<SpriteComponent>().Play("DroneIdle");

	SetName("Drone");

	speed = rand() % (int)3.1f + 3;
	transformComponent = &GetComponent<TransformComponent>();
}

void Drone::Update()
{
	if (IsActive())
	{
		__super::Update();
		
		transformComponent->velocity.y = 1 * speed;
		transformComponent->position.x = startPosition.x + amplitude * std::sin(transformComponent->position.y);
		

		if (transformComponent->position.y > 850)
		{
			Destroy();
		}
	}
}

void Drone::Fire()
{

}

void Drone::BeginOverlap(Entity* otherEntity)
{
	if (otherEntity != this)
	{
		std::cout << "loner collision detected with " << otherEntity->GetName() << std::endl;
	}
}

void Drone::EndOverlap(Entity* otherEntity)
{
}