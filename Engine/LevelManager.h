#pragma once

class LevelManager
{
public:
	LevelManager(class Manager* manager);
	~LevelManager();

	//Create Projectile
	void CreateProjectile(class Vector2D position, int projectileRange, int projectileSpeed);

	//Instantiate Entity
	void Instantiate(class Entity* entity, class Vector2D position);
	
private:
	class Manager* m_manager;
};
