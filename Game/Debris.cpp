#include "Debris.h"
#include "Vector2D.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"

Debris::Debris(bool isLeftDebris)
{
	scrollingSpeed = 0.8f;
	leftDebris = isLeftDebris;
}

Debris::~Debris()
{
	delete spriteComponent;
	delete transformComponent;
	Destroy();
}

void Debris::Init()
{
	__super::Init();


	if (!leftDebris)
	{
		AddComponent<TransformComponent>(590, -950);
		AddComponent<SpriteComponent>("../Assets/graphics/blocksA.bmp", false);
	}
	else
	{
		AddComponent<TransformComponent>(-550, -995);
		AddComponent<SpriteComponent>("../Assets/graphics/blocksB.bmp", false);
	}

	spriteComponent = &GetComponent<SpriteComponent>();
	transformComponent = &GetComponent<TransformComponent>();
}

void Debris::Update()
{
	__super::Update();

	spriteComponent->ChangeSrcRect(1024, 1024);
	spriteComponent->ChangeDstRect(1500, 2800);

	transformComponent->velocity.y = 1 * scrollingSpeed;
	
	if (transformComponent->position.y > 2000)
	{
		Destroy();
	}
}
