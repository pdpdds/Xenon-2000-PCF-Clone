#pragma once

#include <memory>

class LevelManager
{
public:
	LevelManager();
	~LevelManager();

	static class Manager* GetManager();

	static LevelManager* GetInstance()
	{
		return m_instance = (m_instance != nullptr) ? m_instance : new LevelManager();
		delete m_instance;
	}

	void Update();

	//Create Projectile
	void CreateProjectile(class Vector2D position, float projectileRange, float projectileSpeed);

	//Create Projectile
	void CreateLevel();

	void SpawnEnemies();

	void SpawnDebris();

private:
	static Manager* m_manager;
	static LevelManager* m_instance;

	int enemiesToSpawn = 0;

	//Spawn Timers
	float lonerSpawnTimer;
	float lonerSpawnTimerMax;

	float rusherSpawnTimer;
	float rusherSpawnTimerMax;

	float debrisSpawnTimer;
	float debrisSpawnTimerMax;
};
