#pragma once

#include "../Game/Loner.h"

class LevelManager
{
public:
	//LevelManager(class Manager* manager);
	LevelManager();
	~LevelManager();

	static class Manager* GetManager();

	static LevelManager* GetInstance()
	{
		return m_instance = (m_instance != nullptr) ? m_instance : new LevelManager();
	}

	//Create Projectile
	void CreateProjectile(class Vector2D position, int projectileRange, int projectileSpeed);

	////Instantiate Entity
	//void Instantiate(class Entity* entity, class Vector2D position);

	void SpawnEnemies();

private:
	static class Manager* m_manager;
	static LevelManager* m_instance;

	//Enemies Array
	std::vector<Loner*> lonerEnemies;

	//Spawn Timers
	float spawnTimer;
	float spawnTimerMax;

	bool spawning = false;
};
