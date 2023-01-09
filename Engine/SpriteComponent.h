#pragma once

#include <SDL.h>
#include "Components.h"
#include <map>

class TransformComponent;
class SDL_Texture;
class SDL_Rect;

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

	void SetFlashing(bool flashing);

	int m_animIndex = 0;
	
	std::map<const char*, struct Animation> m_animations;

	SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

private:
	TransformComponent* m_transformComponent;
	SDL_Texture* m_texture;
	SDL_Texture* m_whiteTexture;
	SDL_Rect m_srcRect;
	SDL_Rect m_dstRect;

	bool m_animated = false;
	bool m_loopable = false;
	int m_frames = 0;
	int m_speed = 100;

	bool m_flashing = false;
	float m_flashTimer;
};