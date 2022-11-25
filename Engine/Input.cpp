#include "Input.h"
#include "GameEngine.h"

Input* Input::m_instance = nullptr;

Input::Input()
{
	m_keyStates = SDL_GetKeyboardState(nullptr);
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
	return (m_keyStates[key] == 1);
}

void Input::KeyUp()
{
}

void Input::KeyDown()
{
}

