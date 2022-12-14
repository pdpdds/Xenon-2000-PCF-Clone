//#pragma once
//
//#include "GameEngine.h"
//
//class LevelManager
//{
//public:
//	LevelManager()
//	{
//		m_manager = &GameEngine::manager;
//
//		lonerSpawnTimer = 0.f;
//		lonerSpawnTimerMax = 100.f + (rand() % (110 - 100) + 1);
//
//		rusherSpawnTimer = 0.f;
//		rusherSpawnTimerMax = 190 + (rand() % (205 - 190) + 1);
//
//		debrisSpawnTimer = 150.f;
//		debrisSpawnTimerMax = 150 + (rand() % (200 - 150) + 1);
//
//		enemiesToSpawn = 0;
//
//	}
//
//	~LevelManager();
//
//	static class Manager* GetManager();
//
//	static LevelManager* GetInstance()
//	{
//		return m_instance = (m_instance != nullptr) ? m_instance : new LevelManager();
//	}
//
//	virtual void Update();
//
//	template <typename T>
//	void InstantiateProjectile(class Vector2D position, float projectileRange, float projectileSpeed)
//	{
//		LevelManager::GetManager()->CreateEntity<T>(position, projectileRange, projectileSpeed);
//	}
//
//	//Create Projectile
//	void CreateLevel();
//
//	void SpawnEnemies();
//
//	void SpawnDebris();
//
//private:
//	static Manager* m_manager;
//	static LevelManager* m_instance;
//
//	int enemiesToSpawn = 0;
//
//	//Spawn Timers
//	float lonerSpawnTimer;
//	float lonerSpawnTimerMax;
//
//	float rusherSpawnTimer;
//	float rusherSpawnTimerMax;
//
//	float debrisSpawnTimer;
//	float debrisSpawnTimerMax;
//};
