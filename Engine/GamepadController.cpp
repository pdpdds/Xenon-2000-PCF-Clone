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
	switch (GameEngine::event.type)
	{
	case SDL_CONTROLLERBUTTONDOWN:
		switch (GameEngine::event.cbutton.button)
		{
			case SDL_CONTROLLER_BUTTON_DPAD_UP:
				m_transformComponent->velocity.y = -1;
				break;

			case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
				m_transformComponent->velocity.x = -1;
				break;

			case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
				m_transformComponent->velocity.y = 1;
				break;

			case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
				m_transformComponent->velocity.x = 1;
				break;

			case SDL_CONTROLLER_BUTTON_A:
				break;

			default:
				break;
		}
		break;
	case SDL_CONTROLLERBUTTONUP:
		switch (GameEngine::event.cbutton.button)
		{
		case SDL_CONTROLLER_BUTTON_DPAD_UP:
			m_transformComponent->velocity.y = 0;
			break;

		case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
			m_transformComponent->velocity.x = 0;
			break;

		case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
			m_transformComponent->velocity.y = 0;
			break;

		case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
			m_transformComponent->velocity.x = 0;
			break;

		default:
			break;
		}
		break;
	default:
		break;
	}
}
