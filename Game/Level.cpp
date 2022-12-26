#include "Level.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"

Level::Level()
{
	scrollingSpeed = 0.1f;
}

Level::~Level()
{
	delete spriteComponent;
	delete transformComponent;
	Destroy();
}

void Level::Init()
{
	__super::Init();

	AddComponent<TransformComponent>(0,-198);
	AddComponent<SpriteComponent>("../Assets/graphics/galaxy2.bmp", false, false);

	spriteComponent = &GetComponent<SpriteComponent>();
	transformComponent = &GetComponent<TransformComponent>();

	SetName("Background");
}

void Level::Update()
{
	__super::Update();

	spriteComponent->ChangeSrcRect(1000, 1000);
	spriteComponent->ChangeDstRect(1500, 1200);

}
