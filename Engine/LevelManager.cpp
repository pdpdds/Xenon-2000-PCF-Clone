#include "LevelManager.h"
#include "GameEngine.h"
#include "Vector2D.h"
#include "EntityComponentSystem.h"
#include "Projectile.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "GroupLabels.h"
#include <iostream>

LevelManager* LevelManager::m_instance = nullptr;


LevelManager::LevelManager()
{
	m_manager = &GameEngine::manager;
}

LevelManager::~LevelManager()
{
}

Manager* LevelManager::GetManager()
{
	return m_manager;
}


void LevelManager::CreateProjectile(Vector2D position, int projectileRange, int projectileSpeed)
{
	auto* projectile = m_manager->CreateEntity<Projectile>();
	projectile->AddComponent<TransformComponent>(position.x, position.y);
	projectile->AddComponent<SpriteComponent>("../Assets/graphics/missile.bmp", false);
}

//void LevelManager::Instantiate(Entity* entity, Vector2D position)
//{
//	
//}

void LevelManager::SpawnEnemies()
{
	auto* loner = GameEngine::manager.CreateEntity<Loner>();

	spawnTimerMax = 5.f;
	spawnTimer = spawnTimerMax;

	spawning = true;

	while (spawning)
	{
		spawnTimer += 0.5f;

		if (spawnTimer >= spawnTimerMax)
		{
			lonerEnemies.push_back(loner);
			spawnTimer = 0.f;
		}
	}
}

