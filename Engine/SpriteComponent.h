#pragma once

#include "Components.h"

#define TILESIZE 64;

class SpriteComponent : public Component
{
public:
	SpriteComponent() = default;
	SpriteComponent(const char* texPath);

	void Init() override;
	void Update() override;
	void Draw() override;

	void SetTexture(const char* texPath);

private:
	class TransformComponent* m_transformComponent;
	class SDL_Texture* m_texture;
	class SDL_Rect m_srcRect, m_dstRect;
};