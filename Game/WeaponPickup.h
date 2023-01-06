#pragma once

#include "Pickup.h"
#include "Vector2D.h"
#include <vector>

class TransformComponent;

class WeaponPickup : public Pickup
{
public:
	WeaponPickup();
	~WeaponPickup();

	virtual void Init();
	virtual void Update();
	virtual void BeginOverlap(Entity* otherEntity);
	virtual void EndOverlap(Entity* otherEntity);

private:
	Vector2D startPosition;
	float speed;

	TransformComponent* transformComponent = nullptr;
};