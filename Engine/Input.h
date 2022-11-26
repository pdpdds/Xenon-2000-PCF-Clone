#pragma once
#include "SDL.h"

class Input
{
public:
	static Input* GetInstance()
	{
		return m_instance = (m_instance != nullptr) ? m_instance : new Input();
	}

	void Listen();
	bool GetKeyDown(SDL_Scancode key);
	bool GetKeyUp(SDL_Scancode key);

private:
	Input();
	void KeyUp();
	void KeyDown();

	const uint8_t* m_keyStates;
	static Input* m_instance;
};