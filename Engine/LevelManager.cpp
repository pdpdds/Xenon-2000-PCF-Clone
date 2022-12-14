//#include "LevelManager.h"
//#include "GameEngine.h"
//#include "Vector2D.h"
//#include "EntityComponentSystem.h"
//#include "TransformComponent.h"
//#include "SpriteComponent.h"
//#include "GroupLabels.h"
//#include <iostream>
//#include "Projectile.h"
//#include "../Game/Loner.h"
//#include "../Game/Rusher.h"
//#include "../Game/Level.h"
//#include "../Game/Debris.h"
//#include "../Game/PlayerProjectile.h"
//
//LevelManager* LevelManager::m_instance = nullptr;
//Manager* LevelManager::m_manager = nullptr;
//
//
////LevelManager::LevelManager()
////{
////	m_manager = &GameEngine::manager;*/
////
////	lonerSpawnTimer = 0.f;
////	lonerSpawnTimerMax = 100.f + (rand() % (110 - 100) + 1);
////
////	rusherSpawnTimer = 0.f;
////	rusherSpawnTimerMax = 190 + (rand() % (205 - 190) + 1);
////
////	debrisSpawnTimer = 150.f;
////	debrisSpawnTimerMax = 150 + (rand() % (200 - 150) + 1);
////
////	enemiesToSpawn = 0;
////}
//
//LevelManager::~LevelManager()
//{
//	delete m_manager;
//	delete m_instance;
//}
//
//Manager* LevelManager::GetManager()
//{
//	return m_manager;
//}
//
//void LevelManager::Update()
//{
//	SpawnEnemies();
//	SpawnDebris();
//}
//
//void LevelManager::CreateLevel()
//{
//	m_manager->CreateEntity<Level>();
//}
//
//void LevelManager::SpawnEnemies()
//{
//	lonerSpawnTimer += 0.5f;
//	rusherSpawnTimer += + 0.5f;
//
//	if (lonerSpawnTimer >= lonerSpawnTimerMax)
//	{
//		enemiesToSpawn = rand() % 2 + 1;
//
//		for (int i = 0; i < enemiesToSpawn; ++i)
//		{
//			GameEngine::manager.CreateEntity<Loner>();
//		}
//		
//		lonerSpawnTimer = 0.f;
//	}
//
//	if (rusherSpawnTimer >= rusherSpawnTimerMax)
//	{
//		enemiesToSpawn = rand() % 5 + 3;
//
//		for (int i = 0; i < enemiesToSpawn; ++i)
//		{
//			GameEngine::manager.CreateEntity<Rusher>();
//		}
//
//		rusherSpawnTimer = 0.f;
//	}
//}
//
//void LevelManager::SpawnDebris()
//{
//	debrisSpawnTimer += 0.5f;
//
//	if (debrisSpawnTimer >= debrisSpawnTimerMax)
//	{
//		m_manager->CreateEntity<Debris>(true);
//		debrisSpawnTimerMax = 150 + (rand() % (200 - 150) + 1);
//		debrisSpawnTimer = 0.f;
//	}
//}
//
