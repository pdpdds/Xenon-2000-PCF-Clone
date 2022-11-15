#include "PlayerController.h"
#include "EntityComponentSystem.h"
#include "KeyboardController.h"
#include "TransformComponent.h"
#include <stdio.h>

void PlayerController::Init()
{
	m_transformComponent = &m_entity->GetComponent<TransformComponent>();

	if (m_transformComponent)
	{
		std::cout << "Player Controller Initialized on address " << &m_entity << std::endl;
		&m_entity->AddComponent<KeyboardController>();
	}
	else
	{
		std::cout << "Player Controller Failed To Initialize" << std::endl;
	}

}
