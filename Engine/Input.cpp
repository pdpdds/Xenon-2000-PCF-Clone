#include "Input.h"
#include "GameEngine.h"
#include "InitError.h"
#include <iostream>

Input* Input::m_instance = nullptr;
SDL_GameController* controller = nullptr;

Input::Input()
{
	m_keyStates = SDL_GetKeyboardState(nullptr);

	if (SDL_Init(SDL_INIT_GAMECONTROLLER) < 0)
	{
		std::cout << "ERROR: Game Controller failed to initialize" << std::endl;
		throw InitError();
	}
	if (SDL_NumJoysticks() < 1)
	{
		std::cout << "WARNING: No Gamepad detected" << std::endl;
	}
	else
	{
		controller = SDL_GameControllerOpen(0);
	}
}

void Input::Listen()
{
	switch (GameEngine::event.type)
	{
	case SDL_KEYDOWN:
		KeyDown();
		break;
	case SDL_KEYUP:
		KeyUp();
		break;
	}
}

bool Input::GetKeyDown(SDL_Scancode key)
{
	//Returns true if key is being pushed down
	if (m_keyStates[key] == 1)
	{
		return true;
	}
	return false;
}

bool Input::GetKeyUp(SDL_Scancode key)
{
	return false;
}

void Input::KeyUp()
{
	m_keyStates = SDL_GetKeyboardState(nullptr);
}

void Input::KeyDown()
{

}

