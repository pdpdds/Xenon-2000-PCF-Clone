#pragma once

#include "Enemy.h"
#include "Vector2D.h"

class TransformComponent;
class b2World;
class b2Body;
class b2Fixture;

class Loner : public Enemy
{
public:
	Loner();
	~Loner();

	virtual void Init();
	virtual void Update();

	virtual void Fire();

	virtual void BeginOverlap(Entity* otherEntity);
	virtual void EndOverlap(Entity* otherEntity);

	virtual void TakeDamage(float damage);

private:
	Vector2D startPosition;
	Vector2D playerPosition;
	float speed;

	TransformComponent* transformComponent = nullptr;

	//Fire Timers
	float fireTimer;
	float fireTimerMax;

	b2World* m_world;
	b2Body* m_body;
	b2Fixture* m_fixture;
};