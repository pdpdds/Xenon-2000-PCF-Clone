#pragma once

#include <SDL.h>
#include "Components.h"
#include <map>

class SpriteComponent : public Component
{
public:
	SpriteComponent() = default;
	SpriteComponent(const char* texPath);
	SpriteComponent(const char* texPath, bool isAnimated, bool isLoop);
	~SpriteComponent();

	void Init() override;
	void Update() override;
	void Draw() override;

	void Play(const char* animName);

	void SetTexture(const char* texPath);

	void ChangeDstRect(int width, int height) { m_dstRect.w = width; m_dstRect.h = height; }

	void ChangeSrcRect(int width, int height) { m_srcRect.w = width; m_srcRect.h = height; }

	int m_animIndex = 0;
	
	std::map<const char*, struct Animation> m_animations;

	SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

private:
	class TransformComponent* m_transformComponent;
	class SDL_Texture* m_texture;
	class SDL_Rect m_srcRect;
	class SDL_Rect m_dstRect;

	bool m_animated = false;
	bool m_loopable = false;
	int m_frames = 0;
	int m_speed = 100;
};