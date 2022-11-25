#include "LevelManager.h"
#include "EntityComponentSystem.h"
#include "Vector2D.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "PlayerController.h"
#include "ProjectileComponent.h"
#include "GroupLabels.h"
#include <iostream>

LevelManager::LevelManager(Manager* manager) : m_manager(manager)
{
}

LevelManager::~LevelManager()
{
}

void LevelManager::CreateProjectile(Vector2D position, int projectileRange, int projectileSpeed)
{
}

void LevelManager::Instantiate(Entity* entity, Vector2D position)
{
	entity = m_manager->CreateEntity<Entity>();

	//Add Components
	entity->AddComponent<TransformComponent>(position.x, position.y);
	entity->AddComponent<SpriteComponent>("../Assets/graphics/ShipIdle.bmp", false);
	//entity->AddComponent<PlayerController>();
	//entity->AddGroup(Groups::GROUP_PLAYERS);

	////Initialize Entity
	//entity->Init();

	//std::cout << "Instantiated Entity" << std::endl;
}
