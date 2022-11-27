#pragma once

class LevelManager
{
public:
	LevelManager();
	~LevelManager();

	static class Manager* GetManager();

	static LevelManager* GetInstance()
	{
		return m_instance = (m_instance != nullptr) ? m_instance : new LevelManager();
	}

	void Update();

	//Create Projectile
	void CreateProjectile(class Vector2D position, float projectileRange, float projectileSpeed);

	void SpawnEnemies();

private:
	static Manager* m_manager;
	static LevelManager* m_instance;

	int enemiesToSpawn = 0;

	//Spawn Timers
	float lonerSpawnTimer;
	float lonerSpawnTimerMax;

	float rusherSpawnTimer;
	float rusherSpawnTimerMax;
};
