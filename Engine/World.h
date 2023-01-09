#pragma once

#include "../include/Box2D/box2d/box2d.h"
#include <memory>
#include <queue>
#include <functional>

class World : public b2ContactListener 
{
public:

	World();
	~World();

	static World* GetInstance() 
	{
		return m_instance = m_instance != nullptr ? m_instance : new World();
	}

	inline b2World* GetWorld() { return m_world.get(); }

	void Init();
	void Update(float deltaTime);
	virtual void BeginContact(b2Contact* contact) override;
	virtual void EndContact(b2Contact* contact) override;

	void QueueAction(const std::function<void()>& action);


private:
	static World* m_instance;
	std::unique_ptr<b2World> m_world;

	std::vector<std::function<void()>> m_actions;
};