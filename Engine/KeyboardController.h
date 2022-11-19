#pragma once

#include "Components.h"

class KeyboardController : public Component
{
public:
	class TransformComponent* m_transformComponent;
	class SpriteComponent* m_SpriteComponent;

	void Init() override;

	void Update() override;
};