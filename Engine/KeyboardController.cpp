#include "SDL.h"
#include "KeyboardController.h"
#include "GameEngine.h"
#include "EntityComponentSystem.h"
#include "TransformComponent.h"
#include <iostream>

void KeyboardController::Init()
{
	m_transformComponent = &m_entity->GetComponent<TransformComponent>();

	if (m_transformComponent)
	{
		std::cout << "Keyboard Controller Initialized on address " << &m_entity << std::endl;
	}
	else
	{
		std::cout << "Keyboard Controller Failed To Initialize" << std::endl;
	}
}

void KeyboardController::Update()
{
	switch (GameEngine::event.type) {
	case SDL_KEYDOWN:
		switch (GameEngine::event.key.keysym.sym) {
		case SDLK_w:
			m_transformComponent->velocity.y = -1;
			break;
		case SDLK_a:
			m_transformComponent->velocity.x = -1;
			break;
		case SDLK_s:
			m_transformComponent->velocity.y = 1;
			break;
		case SDLK_d:
			m_transformComponent->velocity.x = 1;
			break;
		default:
			break;
		}
		break;
	case SDL_KEYUP:
		switch (GameEngine::event.key.keysym.sym) {
		case SDLK_w:
			m_transformComponent->velocity.y = 0;
			break;
		case SDLK_a:
			m_transformComponent->velocity.x = 0;
			break;
		case SDLK_s:
			m_transformComponent->velocity.y = 0;
			break;
		case SDLK_d:
			m_transformComponent->velocity.x = 0;
			break;
		default:
			break;
		}
	}
}