#include "EntityComponentSystem.h"
#include "Vector2D.h"
#include <iostream>

//void Entity::Instantiate(Entity& entity, Vector2D position)
//{
//	entity = GameEngine::manager.AddEntity();
//	entity.AddComponent<TransformComponent>(position.x, position.y);
//	entity.AddComponent<SpriteComponent>("../Assets/graphics/Ship2.bmp", false);
//	entity.AddComponent<PlayerController>();
//	entity.AddGroup(Groups::GROUP_PLAYERS);
//}

void Entity::AddGroup(Group group)
{
	m_groupBiset[group] = true;
	m_manager->AddToGroup(this, group);
}
