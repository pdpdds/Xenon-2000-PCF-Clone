#include "LevelManager.h"
#include "GameEngine.h"
#include "Vector2D.h"
#include "EntityComponentSystem.h"
#include "Projectile.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "GroupLabels.h"
#include <iostream>
#include "../Game/Loner.h"
#include "../Game/Rusher.h"

LevelManager* LevelManager::m_instance = nullptr;
Manager* LevelManager::m_manager = nullptr;


LevelManager::LevelManager()
{
	m_manager = &GameEngine::manager;

	lonerSpawnTimer = 0.f;
	lonerSpawnTimerMax = rand() % 110 + 100;

	rusherSpawnTimer = 0.f;
	rusherSpawnTimerMax = rand() % 190 + 205;

	enemiesToSpawn = 0;
}

LevelManager::~LevelManager()
{
}

Manager* LevelManager::GetManager()
{
	return m_manager;
}


void LevelManager::Update()
{
	SpawnEnemies();
}

void LevelManager::CreateProjectile(Vector2D position, float projectileRange, float projectileSpeed)
{
	m_manager->CreateEntity<Projectile>(position, projectileRange, projectileSpeed);
}

void LevelManager::SpawnEnemies()
{
	lonerSpawnTimer += 0.5f;
	rusherSpawnTimer += + 0.5f;

	if (lonerSpawnTimer >= lonerSpawnTimerMax)
	{
		enemiesToSpawn = rand() % 2 + 1;

		for (int i = 0; i < enemiesToSpawn; ++i)
		{
			auto* loner = GameEngine::manager.CreateEntity<Loner>();
		}
		
		lonerSpawnTimer = 0.f;
	}

	if (rusherSpawnTimer >= rusherSpawnTimerMax)
	{
		enemiesToSpawn = rand() % 5 + 3;

		for (int i = 0; i < enemiesToSpawn; ++i)
		{
			auto* rusher = GameEngine::manager.CreateEntity<Rusher>();
		}

		rusherSpawnTimer = 0.f;
	}
}

