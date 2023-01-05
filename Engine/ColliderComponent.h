#pragma once

#include "Components.h"
#include "EntityFilters.h"

using CollisionFilter = unsigned short;

class b2World;
class b2Body;
class b2Fixture;

class ColliderComponent : public Component
{
public:
	ColliderComponent(Entity* parent, float width, float height);
	~ColliderComponent();

	void Init() override;
	void Update() override;

	/// Set the collision filter for this body, eg. EntityCategory::PLAYER_BULLET 
	/// @param PLAYER_BULLET.
	/// @param ENEMY.
	void SetCollisionFilter(CollisionFilter collisionFilter, unsigned short maskBit);

	b2Body* GetBody() { return m_body; }

	/// Returns the collision filter for this body
	CollisionFilter GetCollisionFilter() 
	{
		return m_collisionFilter;
	}

	float m_bodyX;
	float m_bodyY;

	inline Entity* GetParent() const { return m_parent; }

private:
	b2World* m_world;
	b2Body* m_body;
	b2Fixture* m_fixture;
	Entity* m_parent;

	CollisionFilter m_collisionFilter;

	float m_width;
	float m_height;
};