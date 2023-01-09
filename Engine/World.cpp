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
	m_world->SetContinuousPhysics(true);
	m_world->SetAllowSleeping(false);
}

void World::Update(float deltaTime)
{
	m_world->DebugDraw();
	m_world->Step(deltaTime, 12, 8);

	for (const std::function<void()>& action : m_actions)
	{
		action();
	}
	m_actions.clear();
}

void World::QueueAction(const std::function<void()>& action)
{
	m_actions.push_back(action);
}

void World::BeginContact(b2Contact* contact)
{
	Entity* bodyA = ((Entity*)contact->GetFixtureA()->GetUserData().pointer);
	Entity* bodyB = ((Entity*)contact->GetFixtureB()->GetUserData().pointer);

	if (bodyA != nullptr && bodyB != nullptr)
	{
		bodyA->BeginOverlap(bodyB);
		bodyB->BeginOverlap(bodyA);
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
