#include "SDL.h"
#include "InputHandler.h"

InputHandler::InputHandler() : keyStates(0)
{

}

void InputHandler::Update()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_KEYDOWN:
			OnKeyDown();
			break;

		case SDL_KEYUP:
			OnKeyUp();
			break;

		default:
			break;
		}
	}
}

void InputHandler::Clean()
{
}

bool InputHandler::IsKeyDown(Keyboard::Keys keyboardKey) const
{
	if (keyStates)
	{
		return keyStates[keyboardKey] ? true : false;
	}
	return false;
}

void InputHandler::OnKeyDown()
{
	keyStates = const_cast<Uint8*>(SDL_GetKeyboardState(0));
}

void InputHandler::OnKeyUp()
{
	keyStates = const_cast<Uint8*>(SDL_GetKeyboardState(0));
}
