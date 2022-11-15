#pragma once

#include "Keycodes.h"
#include <cstdint>

class InputHandler
{
public:
	InputHandler();
	~InputHandler();

	void Init();
	void Update();
	void Clean();

	bool IsKeyDown(Keyboard::Keys keyboardKey) const;

	//Get Input Handler instance
	static InputHandler* GetInstance()
	{
		static InputHandler* inputHandlerInstance = new InputHandler;
		return inputHandlerInstance;
	}

private:
	//Handle Keyboard events
	void OnKeyDown();
	void OnKeyUp();

	//State of the keyboard buttons
	uint8_t* keyStates;
};