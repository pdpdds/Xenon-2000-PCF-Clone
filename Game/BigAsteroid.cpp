#include "BigAsteroid.h"
#include "ColliderComponent.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "LogOutput.h"
#include "GameManager.h"
#include "World.h"
#include "Vector2D.h"
#include "MediumAsteroid.h"
#include <iostream>
#include <random>

BigAsteroid::BigAsteroid()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(-160, -130); 
	int randNum = dis(gen); 

	startPosition = Vector2D(rand() % 910, randNum);
	speed = 0.f;
	maxHP = 200.f;
	hp = maxHP;
}

BigAsteroid::~BigAsteroid()
{
}

void BigAsteroid::Init()
{
	__super::Init();

	AddComponent<TransformComponent>(startPosition.x, startPosition.y);
	AddComponent<SpriteComponent>("../Assets/graphics/SAster96A.bmp", false, false);
	AddComponent<ColliderComponent>(this, 96, 96);

	SetName("BigAsteroid");
	SetTag(Tag::Asteroid);

	speed = 1.5f;
	transformComponent = &GetComponent<TransformComponent>();
	spriteComponent = &GetComponent<SpriteComponent>();
}

void BigAsteroid::Update()
{
	__super::Update();

	spriteComponent->ChangeSrcRect(96, 96);
	spriteComponent->ChangeDstRect(96, 96);

	transformComponent->velocity.y = 1 * speed;

	if (transformComponent->position.y > 850)
	{
		Destroy();
	}
}

void BigAsteroid::Break()
{
	Destroyed(this);
	this->m_destroyed = true;
}

void BigAsteroid::TakeDamage(float damage)
{
	hp -= damage;

	if (this->hp <= 0)
	{
		World::GetInstance()->QueueAction([&]() { CreateNewAsteroids(); });
		Break();
	}
}

void BigAsteroid::CreateNewAsteroids()
{
	// Seed the random number generator with the current time
	std::srand(std::time(nullptr));

	// Generate three random integers between -1 and 1 (inclusive)
	int xDirection1 = std::rand() % 3 - 2;
	int xDirection2 = std::rand() % 3 - 2;
	int xDirection3 = std::rand() % 3 - 2;

	MediumAsteroid* asteroid1 = GameManager::GetManager()->CreateEntity<MediumAsteroid>();
	asteroid1->GetComponent<TransformComponent>().position = transformComponent->position;
	// Set the velocity of the asteroid based on the random x direction
	asteroid1->GetComponent<TransformComponent>().velocity.x = xDirection1;
	// Set the velocity of the asteroid in the y direction to a random value
	asteroid1->GetComponent<TransformComponent>().velocity.y = std::rand() % 5 - 4;

	MediumAsteroid* asteroid2 = GameManager::GetManager()->CreateEntity<MediumAsteroid>();
	asteroid2->GetComponent<TransformComponent>().position = transformComponent->position;
	// Set the velocity of the asteroid based on the random x direction
	asteroid2->GetComponent<TransformComponent>().velocity.x = xDirection2;
	// Set the velocity of the asteroid in the y direction to a random value
	asteroid2->GetComponent<TransformComponent>().velocity.y = std::rand() % 5 - 4;

	MediumAsteroid* asteroid3 = GameManager::GetManager()->CreateEntity<MediumAsteroid>();
	asteroid3->GetComponent<TransformComponent>().position = transformComponent->position;
	// Set the velocity of the asteroid based on the random x direction
	asteroid3->GetComponent<TransformComponent>().velocity.x = xDirection3;
	// Set the velocity of the asteroid in the y direction to a random value
	asteroid3->GetComponent<TransformComponent>().velocity.y = std::rand() % 5 - 4;
}

void BigAsteroid::BeginOverlap(Entity* otherEntity)
{
	if (otherEntity->GetTag() == Tag::Player)
	{
		otherEntity->TakeDamage(18.f);
	}

	if (otherEntity->GetTag() == Tag::Projectile)
	{
		GetComponent<SpriteComponent>().SetFlashing(true);
	}
}

void BigAsteroid::EndOverlap(Entity* otherEntity)
{
	if (otherEntity->GetTag() == Tag::Projectile)
	{
		GetComponent<SpriteComponent>().SetFlashing(false);
	}
}
