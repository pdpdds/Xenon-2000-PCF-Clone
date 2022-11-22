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
	//switch (GameEngine::event.type)
	//{
	//case SDL_JOYAXISMOTION:  /* Handle Joystick Motion */
	//	if ((GameEngine::event.jaxis.value < -3200) || (GameEngine::event.jaxis.value > 3200))
	//	{
	//		if (GameEngine::event.jaxis.axis == 0)
	//		{
	//			std::cout << "Left-right" << std::endl;
	//			/* Left-right movement code goes here */
	//		}

	//		if (GameEngine::event.jaxis.axis == 1)
	//		{
	//			std::cout << "Up-down" << std::endl;
	//			/* Up-Down movement code goes here */
	//		}
	//	}
	//	break;
	////case SDL_KEYUP:
	////	switch (GameEngine::event.key.keysym.sym) {
	////	case SDLK_w:
	////		m_transformComponent->velocity.y = 0;
	////		//m_SpriteComponent->Play("Idle");
	////		break;
	////	case SDLK_a:
	////		m_transformComponent->velocity.x = 0;
	////		//m_SpriteComponent->Play("Idle");
	////		break;
	////	case SDLK_s:
	////		m_transformComponent->velocity.y = 0;
	////		//m_SpriteComponent->Play("Idle");
	////		break;
	////	case SDLK_d:
	////		m_transformComponent->velocity.x = 0;
	////		//m_SpriteComponent->Play("Idle");
	////		break;
	////	default:
	////		break;
	////	}
	//}
}
