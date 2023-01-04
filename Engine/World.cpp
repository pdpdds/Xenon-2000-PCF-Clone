#include "World.h"
#include "EntityComponentSystem.h"

World* World::m_instance = nullptr;

World::World()
{
}

World::~World()
{
	delete m_instance;
}

void World::Init()
{
	b2Vec2 gravity(0.0f, 0.0f);
	m_world = std::make_unique<b2World>(gravity);

	m_world->SetContactListener(this);
}

void World::Update(float deltaTime)
{
	m_world->SetContinuousPhysics(true);
	m_world->DebugDraw();
	m_world->Step(deltaTime, 36, 28);
}

void World::BeginContact(b2Contact* contact)
{
	//Get the body A's entity 
	Entity* bodyA = ((Entity*)contact->GetFixtureA()->GetUserData().pointer);
	//Get the body B's entity 
	Entity* bodyB = ((Entity*)contact->GetFixtureB()->GetUserData().pointer);

	//If none of the bodies are null
	if (bodyA != nullptr && bodyB != nullptr)
	{
		((Entity*)bodyA)->BeginOverlap(((Entity*)bodyB));
		((Entity*)bodyB)->BeginOverlap(((Entity*)bodyA));
	}
}

void World::EndContact(b2Contact* contact)
{
	Entity* bodyA = ((Entity*)contact->GetFixtureA()->GetUserData().pointer);
	Entity* bodyB = ((Entity*)contact->GetFixtureB()->GetUserData().pointer);

	if (bodyA != nullptr && bodyB != nullptr)
	{
		((Entity*)bodyA)->EndOverlap(((Entity*)bodyB));
		((Entity*)bodyB)->EndOverlap(((Entity*)bodyA));
	}
}
