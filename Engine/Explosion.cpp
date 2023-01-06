#include "Explosion.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "LogOutput.h"
#include <chrono>
#include <thread>

Explosion::Explosion(Vector2D position)
{
	startPosition = position;
}

Explosion::~Explosion()
{

}

void Explosion::Init()
{
	__super::Init();

	AddComponent<TransformComponent>(startPosition.x, startPosition.y);
	AddComponent<SpriteComponent>("../Assets/graphics/explosion.bmp", true, true);
	GetComponent<SpriteComponent>().Play("Explosion");
	explosionTimer = 2.3f;
}

void Explosion::Update()
{
	__super::Update();

	if (explosionTimer > 0.0f)
	{
		explosionTimer -= 0.1f;

		// If the timer has expired, destroy the projectile
		if (explosionTimer <= 0.0f)
		{
			Destroy();
		}
	}
}
