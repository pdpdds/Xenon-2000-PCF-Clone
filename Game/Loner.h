#pragma once

#include "Pawn.h"
#include "Vector2D.h"

class TransformComponent;

class Loner : public Pawn
{
public:
	Loner();
	~Loner();

	virtual void Init();
	virtual void Update();

	virtual void Fire();

	virtual void BeginOverlap(Entity* otherEntity);
	virtual void EndOverlap(Entity* otherEntity);

private:
	Vector2D startPosition;
	Vector2D playerPosition;
	float speed;

	TransformComponent* transformComponent = nullptr;

	//Fire Timers
	float fireTimer;
	float fireTimerMax;
};