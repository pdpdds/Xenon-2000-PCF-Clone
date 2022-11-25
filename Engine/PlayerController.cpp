#include "PlayerController.h"
#include "EntityComponentSystem.h"
#include "KeyboardController.h"
#include "GamepadController.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include <stdio.h>

void PlayerController::Init()
{
	m_transformComponent = &entity->GetComponent<TransformComponent>();
	m_spriteComponent = &entity->GetComponent<SpriteComponent>();

	if (m_transformComponent && m_spriteComponent)
	{
		std::cout << "Player Controller Initialized" << std::endl;
		&entity->AddComponent<KeyboardController>();
		&entity->AddComponent<GamepadController>();
	}
	else
	{
		std::cout << "ERROR: Player Controller Failed To Initialize" << std::endl;
	}

}
