#pragma once

#include "Components.h"

class KeyboardController : public Component
{
public:
	class TransformComponent* m_transformComponent;

	void Init() override;

	void Update() override;
};