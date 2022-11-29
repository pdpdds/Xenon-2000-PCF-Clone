#include "Loner.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "GroupLabels.h"

Loner::Loner()
{
	startPosition = Vector2D(1000.f, rand() % 400);
	speed = 0.f;
}

Loner::~Loner()
{
	Destroy();
	delete &this->GetComponent<SpriteComponent>();
	delete transformComponent;
}

void Loner::Init()
{
	__super::Init();

	AddComponent<TransformComponent>(startPosition.x, startPosition.y);
	AddComponent<SpriteComponent>("../Assets/graphics/LonerA.bmp", true, true);
	GetComponent<SpriteComponent>().Play("EnemyIdle");

	speed = rand() % (int)3.3f + 3;
	transformComponent = &GetComponent<TransformComponent>();
}

void Loner::Update()
{
	__super::Update();
	
	transformComponent->velocity.x = -1 * speed;
	
	if (transformComponent->position.x < -50)
	{
		Destroy();
	}
}

void Loner::Fire()
{
}
