#include "CollisionComponent.h"
#include "TransformComponent.h"
#include <cstddef>

CollisionComponent::CollisionComponent()
{
}

void CollisionComponent::Init()
{	
	if (&entity->GetComponent<TransformComponent>() == nullptr)
	{
		entity->AddComponent<TransformComponent>();
	}

	transformComponent = &entity->GetComponent<TransformComponent>();
	
}

void CollisionComponent::Update()
{
	collider.x = static_cast<int>(transformComponent->position.x);
	collider.y = static_cast<int>(transformComponent->position.y);
	collider.w = transformComponent->width * 1;
	collider.h = transformComponent->height * 1;
}
