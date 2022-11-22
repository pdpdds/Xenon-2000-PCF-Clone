#include "SDL.h"
#include "GamepadController.h"
#include "GameEngine.h"
#include "EntityComponentSystem.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include <iostream>

void GamepadController::Init()
{
	m_transformComponent = &m_entity->GetComponent<TransformComponent>();
	m_SpriteComponent = &m_entity->GetComponent<SpriteComponent>();

	if (m_transformComponent)
	{
		std::cout << "Gamepad Controller Initialized" << std::endl;
	}
	else
	{
		std::cout << "ERROR: Gamepad Controller Failed To Initialize" << std::endl;
	}
}

void GamepadController::Update()
{
	/*switch (GameEngine::event.type)
	{
	case SDL_CONTROLLERBUTTONDOWN:
		std::cout << "SDL_CONTROLLERBUTTONDOWN" << std::endl;
		break;
	default:
		break;
	}*/
}
