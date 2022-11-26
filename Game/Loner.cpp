#include "Loner.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "Window.h"

Loner::Loner()
{
	playerStartPosition = Vector2D(950.f, 0.f);
	playerSpeed = 0.f;
}

void Loner::Init()
{
	__super::Init();

	AddComponent<TransformComponent>(playerStartPosition.x, playerStartPosition.y);
	AddComponent<SpriteComponent>("../Assets/graphics/LonerA.bmp", true);
	GetComponent<SpriteComponent>().Play("EnemyIdle");

	playerSpeed = 2.f;
	playerTransform = &GetComponent<TransformComponent>();

	std::cout << "Loner Initialized" << std::endl;
}

void Loner::Update()
{
	__super::Update();

	GetComponent<TransformComponent>().velocity.x = -1 * playerSpeed;
}

void Loner::Fire()
{
}
