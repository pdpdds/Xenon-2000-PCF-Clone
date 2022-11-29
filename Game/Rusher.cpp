#include "Rusher.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "GroupLabels.h"

Rusher::Rusher()
{
	startPosition = Vector2D(rand() % 950, (rand() > RAND_MAX / 2) ? 1 : 830);
	speed = 0.f;
}

Rusher::~Rusher()
{
	std::cout << "rusher out" << std::endl;
	Destroy();
	delete &this->GetComponent<SpriteComponent>();
	delete transformComponent;
}

void Rusher::Init()
{
	__super::Init();

	AddComponent<TransformComponent>(startPosition.x, startPosition.y);
	AddComponent<SpriteComponent>("../Assets/graphics/rusherB.bmp", true, true);
	GetComponent<SpriteComponent>().Play("EnemyIdle");

	speed = rand() % 4 + (int)3.5f;
	transformComponent = &GetComponent<TransformComponent>();
}

void Rusher::Update()
{
	__super::Update();

	if (startPosition.y == 830)
	{
		transformComponent->velocity.y = -1 * speed;
	}
	else
	{
		transformComponent->velocity.y = 1 * speed;
	}
	

	if (transformComponent->position.y < -30 || transformComponent->position.y > 850)
	{
		Destroy();
	}
}

void Rusher::Fire()
{
}
