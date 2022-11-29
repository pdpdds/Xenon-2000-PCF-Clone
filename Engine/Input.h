#pragma once
#include "SDL.h"

class Input
{
public:
	static Input* GetInstance()
	{
		return m_instance = (m_instance != nullptr) ? m_instance : new Input();
		delete m_instance;
	}

	void Listen();
	bool GetKeyDown(SDL_Scancode key);
	bool GetKeyUp(SDL_Scancode key);

	bool GetButtonDown(SDL_GameControllerButton button);
	bool GetButtonUp(SDL_GameControllerButton button);

	int GetAxis(SDL_GameControllerAxis axis);

private:
	Input();
	~Input();
	void KeyUp();
	void KeyDown();

	void Axis();

	void ButtonUp();
	void ButtonDown();

	const uint8_t* m_keyStates;
	static Input* m_instance;
};