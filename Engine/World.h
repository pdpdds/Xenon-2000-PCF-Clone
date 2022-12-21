#pragma once

#include <box2d/box2d.h>
#include <memory>

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
	void BeginContact(b2Contact* contact);

private:
	static World* m_instance;
	std::unique_ptr<b2World> m_world;
};