#pragma once

#include "SDL.h"
#include "Components.h"
#include <map>

class SpriteComponent : public Component
{
public:
	SpriteComponent() = default;
	SpriteComponent(const char* texPath);
	SpriteComponent(const char* texPath, bool isAnimated);
	~SpriteComponent();

	void Init() override;
	void Update() override;
	void Draw() override;

	void Play(const char* animName);

	void SetTexture(const char* texPath);

	int m_animIndex = 0;
	
	std::map<const char*, struct Animation> m_animations;

private:
	class TransformComponent* m_transformComponent;
	class SDL_Texture* m_texture;
	class SDL_Rect m_srcRect;
	class SDL_Rect m_dstRect;

	bool m_animated = false;
	int m_frames = 0;
	int m_speed = 100;
};