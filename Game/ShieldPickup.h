#pragma once

#include "Pickup.h"
#include "Vector2D.h"

class TransformComponent;

class ShieldPickup : public Pickup
{
public:
	ShieldPickup();
	~ShieldPickup();

	virtual void Init();
	virtual void Update();
	virtual void BeginOverlap(Entity* otherEntity);
	virtual void EndOverlap(Entity* otherEntity);

private:
	Vector2D startPosition;
	float speed;

	float healthBoost;

	TransformComponent* transformComponent = nullptr;
};