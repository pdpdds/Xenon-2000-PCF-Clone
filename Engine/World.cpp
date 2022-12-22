#include "World.h"
#include "box2d/box2d.h"
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
	m_world->Step(deltaTime, 6, 2);
}

void World::BeginContact(b2Contact* contact)
{
	Entity* bodyA = ((Entity*)contact->GetFixtureA()->GetUserData().pointer);
	Entity* bodyB = ((Entity*)contact->GetFixtureB()->GetUserData().pointer);

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
