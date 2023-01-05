#include "Rusher.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "GroupLabels.h"
#include <ColliderComponent.h>

Rusher::Rusher()
{
	startPosition = Vector2D(rand() % 950, (rand() > RAND_MAX / 2) ? 1 : 830);
	speed = 0.f;

	this->maxHp = 100.f;
	this->hp = this->maxHp;
}

Rusher::~Rusher()
{

}

void Rusher::Init()
{
	__super::Init();

	AddComponent<TransformComponent>(startPosition.x, startPosition.y);
	AddComponent<SpriteComponent>("../Assets/graphics/rusherB.bmp", true, true);
	AddComponent<ColliderComponent>(this, 64, 64);
	//GetComponent<ColliderComponent>().SetCollisionFilter(EntityCategory::ENEMY, 0x0001);
	GetComponent<SpriteComponent>().Play("EnemyIdle");

	SetName("Rusher");
	SetTag(Tag::Enemy);

	speed = rand() % 3 + (int)2.8f;
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

void Rusher::BeginOverlap(Entity* otherEntity)
{

}

void Rusher::EndOverlap(Entity* otherEntity)
{
}

void Rusher::Fire()
{
}

void Rusher::TakeDamage(float damage)
{
	this->hp -= damage;

	if (this->hp <= 0)
	{
		Destroy();
	}
}
