#include "MediumAsteroid.h"
#include "ColliderComponent.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "LogOutput.h"
#include "GameManager.h"
#include "World.h"
#include "Vector2D.h"
#include "SmallAsteroid.h"

MediumAsteroid::MediumAsteroid()
{
	startPosition = Vector2D(rand() % 950, 0);
	speed = 0.f;
	maxHP = 150.f;
	hp = maxHP;
}

MediumAsteroid::~MediumAsteroid()
{
}

void MediumAsteroid::Init()
{
	__super::Init();

	AddComponent<TransformComponent>(startPosition.x, startPosition.y);
	AddComponent<SpriteComponent>("../Assets/graphics/SAster64.bmp", false, false);
	AddComponent<ColliderComponent>(this, 64, 64);

	SetName("MediumAsteroid");
	SetTag(Tag::Asteroid);

	speed = 2.5f;
	transformComponent = &GetComponent<TransformComponent>();
	spriteComponent = &GetComponent<SpriteComponent>();
}

void MediumAsteroid::Update()
{
	__super::Update();

	transformComponent->velocity.y = 1 * speed;

	if (transformComponent->position.y > 850)
	{
		Destroy();
	}
}

void MediumAsteroid::Break()
{
	Destroyed(this);
	this->m_destroyed = true;
}

void MediumAsteroid::TakeDamage(float damage)
{
	hp -= damage;

	if (this->hp <= 0)
	{
		World::GetInstance()->QueueAction([&]() { CreateNewAsteroids(); });
		Break();
	}
}

void MediumAsteroid::BeginOverlap(Entity* otherEntity)
{
	if (otherEntity->GetTag() == Tag::Player)
	{
		otherEntity->TakeDamage(15.f);
	}

	if (otherEntity->GetTag() == Tag::Projectile)
	{
		GetComponent<SpriteComponent>().SetFlashing(true);
	}
}

void MediumAsteroid::EndOverlap(Entity* otherEntity)
{
	if (otherEntity->GetTag() == Tag::Projectile)
	{
		GetComponent<SpriteComponent>().SetFlashing(false);
	}
}

void MediumAsteroid::CreateNewAsteroids()
{
	// Seed the random number generator with the current time
	std::srand(std::time(nullptr));

	// Generate three random integers between -1 and 1 (inclusive)
	int xDirection1 = std::rand() % 3 - 2;
	int xDirection2 = std::rand() % 3 - 2;
	int xDirection3 = std::rand() % 3 - 2;

	SmallAsteroid* asteroid1 = GameManager::GetManager()->CreateEntity<SmallAsteroid>();
	asteroid1->GetComponent<TransformComponent>().position = transformComponent->position;
	// Set the velocity of the asteroid based on the random x direction
	asteroid1->GetComponent<TransformComponent>().velocity.x = xDirection1;
	// Set the velocity of the asteroid in the y direction to a random value
	asteroid1->GetComponent<TransformComponent>().velocity.y = std::rand() % 5 - 4;

	SmallAsteroid* asteroid2 = GameManager::GetManager()->CreateEntity<SmallAsteroid>();
	asteroid2->GetComponent<TransformComponent>().position = transformComponent->position;
	// Set the velocity of the asteroid based on the random x direction
	asteroid2->GetComponent<TransformComponent>().velocity.x = xDirection2;
	// Set the velocity of the asteroid in the y direction to a random value
	asteroid2->GetComponent<TransformComponent>().velocity.y = std::rand() % 5 - 4;

	SmallAsteroid* asteroid3 = GameManager::GetManager()->CreateEntity<SmallAsteroid>();
	asteroid3->GetComponent<TransformComponent>().position = transformComponent->position;
	// Set the velocity of the asteroid based on the random x direction
	asteroid3->GetComponent<TransformComponent>().velocity.x = xDirection3;
	// Set the velocity of the asteroid in the y direction to a random value
	asteroid3->GetComponent<TransformComponent>().velocity.y = std::rand() % 5 - 4;
}
