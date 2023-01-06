#pragma once

#include "Pickup.h"
#include "Vector2D.h"

class TransformComponent;

class CompanionPickup : public Pickup
{
public:
	CompanionPickup();
	~CompanionPickup();

	virtual void Init();
	virtual void Update();
	virtual void BeginOverlap(Entity* otherEntity);
	virtual void EndOverlap(Entity* otherEntity);

private:
	Vector2D startPosition;
	float speed;

	TransformComponent* transformComponent = nullptr;
};