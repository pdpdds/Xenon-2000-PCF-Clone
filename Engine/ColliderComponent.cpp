#include <SDL.h>
#include "ColliderComponent.h"
#include <box2d/box2d.h>
#include "TransformComponent.h"
#include "World.h"

ColliderComponent::ColliderComponent(Entity* parent, float width, float height)
{
	m_world = World::GetInstance()->GetWorld();
	m_parent = parent;
	m_width = width;
	m_height = height;
}

ColliderComponent::~ColliderComponent()
{
	m_world->DestroyBody(m_body);
	m_body = nullptr;
	m_fixture = nullptr;
	this->m_destroyed = true;
}

void ColliderComponent::Init()
{
	if (!World::GetInstance()->GetWorld()->IsLocked())
	{
	
		//dynamic body for the collider
		b2BodyDef bodyDef;
		bodyDef.type = b2_dynamicBody;
		bodyDef.position.Set(m_parent->GetComponent<TransformComponent>().position.x,
			m_parent->GetComponent<TransformComponent>().position.y);
		bodyDef.fixedRotation = true;
		bodyDef.gravityScale = 0.f;
		bodyDef.bullet = true;


		m_body = m_world->CreateBody(&bodyDef);

		m_bodyX = m_body->GetPosition().x;
		m_bodyY = m_body->GetPosition().y;

		//Create box shape for the collider
		b2PolygonShape shape;
		shape.SetAsBox(m_width / 2, m_height / 2);

		//Create fixture for the collider and attach it to the body
		b2FixtureDef fixtureDef;
		fixtureDef.shape = &shape;
		fixtureDef.density = 1.0f;
		fixtureDef.friction = 0.3f;
		fixtureDef.isSensor = true;
		fixtureDef.userData.pointer = (uintptr_t)m_parent;

		m_fixture = m_body->CreateFixture(&fixtureDef);
	}
}

void ColliderComponent::Update()
{
	if (this->m_destroyed) return;

	if (m_parent && !m_parent->m_destroyed)
	{
		m_body->SetTransform(b2Vec2(m_parent->GetComponent<TransformComponent>().position.x,
			m_parent->GetComponent<TransformComponent>().position.y), m_body->GetAngle());
	}
}

void ColliderComponent::SetCollisionFilter(CollisionFilter collisionFilter, unsigned short maskBit)
{
	m_collisionFilter = collisionFilter;	

	b2Filter filter;	
	filter.categoryBits = m_collisionFilter;
	filter.maskBits = maskBit;
	filter.groupIndex = 0;

	m_fixture->SetFilterData(filter);
}
