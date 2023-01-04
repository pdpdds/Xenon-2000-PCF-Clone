#pragma once

#include <SDL.h>
#include <string.h>
#include "Components.h"

class TransformComponent;

class CollisionComponent : public Component
{
public:
	CollisionComponent();

	void Init() override;

	void Update() override;

	SDL_Rect collider;

	TransformComponent* transformComponent = nullptr;
};