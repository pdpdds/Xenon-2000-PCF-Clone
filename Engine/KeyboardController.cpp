#include "SDL.h"
#include "KeyboardController.h"
#include "GameEngine.h"
#include "EntityComponentSystem.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include <iostream>

void KeyboardController::Init()
{
	m_transformComponent = &m_entity->GetComponent<TransformComponent>();
	m_SpriteComponent = &m_entity->GetComponent<SpriteComponent>();

	if (m_transformComponent)
	{
		std::cout << "Keyboard Controller Initialized" << std::endl;
	}
	else
	{
		std::cout << "ERROR: Keyboard Controller Failed To Initialize" << std::endl;
	}
}

void KeyboardController::Update()
{
	switch (GameEngine::event.type) 
	{
	case SDL_KEYDOWN:
		switch (GameEngine::event.key.keysym.sym) {
		case SDLK_w:
			m_transformComponent->velocity.y = -1;
			//m_SpriteComponent->Play("Idle");
			break;
		case SDLK_a:
			m_transformComponent->velocity.x = -1;
			//m_SpriteComponent->Play("TurnRight");
			break;
		case SDLK_s:
			m_transformComponent->velocity.y = 1;
			//m_SpriteComponent->Play("Idle");
			break;
		case SDLK_d:
			m_transformComponent->velocity.x = 1;
			//m_SpriteComponent->Play("TurnRight");
			break;
		case SDLK_SPACE:
			std::cout << "Fire" << std::endl;
		default:
			break;
		}
		break;
	case SDL_KEYUP:
		switch (GameEngine::event.key.keysym.sym) {
		case SDLK_w:
			m_transformComponent->velocity.y = 0;
			//m_SpriteComponent->Play("Idle");
			break;
		case SDLK_a:
			m_transformComponent->velocity.x = 0;
			//m_SpriteComponent->Play("Idle");
			break;
		case SDLK_s:
			m_transformComponent->velocity.y = 0;
			//m_SpriteComponent->Play("Idle");
			break;
		case SDLK_d:
			m_transformComponent->velocity.x = 0;
			//m_SpriteComponent->Play("Idle");
			break;
		default:
			break;
		}
	}
}