#include "PlayerController.h"
#include "EntityComponentSystem.h"
#include "KeyboardController.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include <stdio.h>

void PlayerController::Init()
{
	m_transformComponent = &m_entity->GetComponent<TransformComponent>();
	m_spriteComponent = &m_entity->GetComponent<SpriteComponent>();

	if (m_transformComponent && m_spriteComponent)
	{
		std::cout << "Player Controller Initialized" << std::endl;
		&m_entity->AddComponent<KeyboardController>();
	}
	else
	{
		std::cout << "ERROR: Player Controller Failed To Initialize" << std::endl;
	}

}
