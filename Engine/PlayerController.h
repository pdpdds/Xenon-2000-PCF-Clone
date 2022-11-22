#pragma once

#include "Components.h"

class PlayerController : public Component
{
public:
	void Init() override;

private:
	class KeyboardController* m_keyboardController;
	class GamepadController* m_gamepadController;
	class TransformComponent* m_transformComponent;
	class SpriteComponent* m_spriteComponent;
};
