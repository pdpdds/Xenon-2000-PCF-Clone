#include "Debris.h"
#include "Vector2D.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"

Debris::Debris(bool isAlive)
{
	scrollingSpeed = 3.0f;
	isActive = isAlive;
}

Debris::~Debris()
{

}

void Debris::Init()
{
	__super::Init();

	SetName("Debris");

	whichDebris = rand() % 2;
	std::cout << whichDebris << std::endl;
	if (whichDebris == 0)
	{
		horizontalMargin = 550 + ( rand() % (700 - 550) + 1);
		verticalMargin = -1100 + ( rand() % (-950 - -1100 + 1));
		std::cout << horizontalMargin << std::endl;
		std::cout << verticalMargin << std::endl;
		AddComponent<TransformComponent>(horizontalMargin, verticalMargin);
		AddComponent<SpriteComponent>("../Assets/graphics/blocksA.bmp", false, false);
	}
	else if (whichDebris == 1)
	{
		horizontalMargin = -300 + (rand() % (-150 - -300) + 1);
		verticalMargin = -1100 + (rand() % (-950 - -1100 + 1));

		//std::cout << horizontalMargin << std::endl;
		//std::cout << verticalMargin << std::endl;
		AddComponent<TransformComponent>(horizontalMargin, verticalMargin);
		AddComponent<SpriteComponent>("../Assets/graphics/blocksB.bmp", false, false);
	}

	spriteComponent = &GetComponent<SpriteComponent>();
	transformComponent = &GetComponent<TransformComponent>();
}

void Debris::Update()
{
	__super::Update();

	spriteComponent->ChangeSrcRect(1024, 2048);
	spriteComponent->ChangeDstRect(1024, 2048);

	transformComponent->velocity.y = 1 * scrollingSpeed;
	
	if (transformComponent->position.y > 2000)
	{
		Destroy();
	}
}
