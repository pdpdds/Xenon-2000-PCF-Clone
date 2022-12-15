#include "EntityComponentSystem.h"
#include "Vector2D.h"
#include <iostream>

void Entity::AddGroup(Group group)
{
	m_groupBiset[group] = true;
	m_manager->AddToGroup(this, group);
}
