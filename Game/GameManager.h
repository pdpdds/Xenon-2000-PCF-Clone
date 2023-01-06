#pragma once

#include "GameEngine.h"

class GameManager
{
public:
	GameManager()
	{
		m_manager = &GameEngine::manager;

		lonerSpawnTimer = 0.f;
		lonerSpawnTimerMax = 100.f + (rand() % (110 - 100) + 1);

		rusherSpawnTimer = 0.f;
		rusherSpawnTimerMax = 190 + (rand() % (205 - 190) + 1);

		debrisSpawnTimer = 150.f;
		debrisSpawnTimerMax = 150 + (rand() % (200 - 150) + 1);

		droneSpawnTimer = 0.f;
		droneSpawnTimerMax = 130.f + (rand() % (140 - 130) + 1);

		weaponPickupSpawnTimer = 0.f;
		weaponPickupSpawnTimerMax = 200.f + (rand() % (210 - 200) + 1);

		enemiesToSpawn = 0;
		pickupsToSpawn = 0;
	}

	~GameManager();

	static class Manager* GetManager();

	static GameManager* GetInstance()
	{
		return m_instance = (m_instance != nullptr) ? m_instance : new GameManager();
	}

	void Update();

	template <typename T>
	void InstantiateProjectile(class Vector2D position, float projectileRange, float projectileSpeed)
	{
		GameManager::GetManager()->CreateEntity<T>(position, projectileRange, projectileSpeed);
	}

	//Create Projectile
	void CreateLevel();

	void SpawnEnemies();

	void SpawnDebris();

	void SpawnPickups();

private:
	static Manager* m_manager;
	static GameManager* m_instance;

	int enemiesToSpawn;

	//Spawn Timers
	float lonerSpawnTimer;
	float lonerSpawnTimerMax;

	float rusherSpawnTimer;
	float rusherSpawnTimerMax;

	float droneSpawnTimer;
	float droneSpawnTimerMax;

	float debrisSpawnTimer;
	float debrisSpawnTimerMax;

	float weaponPickupSpawnTimer;
	float weaponPickupSpawnTimerMax;

	int pickupsToSpawn;
};
