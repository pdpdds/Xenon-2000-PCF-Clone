#include "Asteroid.h"
#include "GameManager.h"
#include "Explosion.h"
#include "TransformComponent.h"

Asteroid::Asteroid()
{
}

Asteroid::~Asteroid()
{
}

void Asteroid::Init()
{
	__super::Init();
}

void Asteroid::Update()
{
	__super::Update();
}

void Asteroid::Break()
{
	Destroy();
}

void Asteroid::Destroyed(Entity* entity)
{
	GameManager::GetManager()->CreateEntity<Explosion>(entity->GetComponent<TransformComponent>().position);
	entity->Destroy();
}
