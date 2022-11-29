#include <SDL.h>
#include "SpriteComponent.h"
#include "TransformComponent.h"
#include "Texture.h"
#include "Animation.h"

SpriteComponent::SpriteComponent(const char* texPath)
{
	SetTexture(texPath);
}

SpriteComponent::SpriteComponent(const char* texPath, bool isAnimated, bool isLoop)
{
	m_animated = isAnimated;
	m_loopable = isLoop;

	Animation m_playerIdle = Animation(0, 1, 1000);
	Animation m_playerTurnRight = Animation(1, 3, 300);

	Animation m_enemyIdle = Animation(0, 4, 200);

	m_animations.emplace("PlayerIdle", m_playerIdle);
	m_animations.emplace("PlayerTurnRight", m_playerTurnRight);
	m_animations.emplace("EnemyIdle", m_enemyIdle);

	SetTexture(texPath);
}

SpriteComponent::~SpriteComponent()
{
	delete m_transformComponent;
	SDL_DestroyTexture(m_texture);
}

void SpriteComponent::Init()
{
	m_transformComponent = &entity->GetComponent<TransformComponent>();

	m_srcRect.x = m_srcRect.y = 0;
	m_srcRect.w = m_transformComponent->width;
	m_srcRect.h = m_transformComponent->height;
}

void SpriteComponent::Update()
{
	if (m_animated && m_loopable)
	{
		m_srcRect.x = m_srcRect.w * static_cast<int>((SDL_GetTicks() / m_speed) % m_frames);
	}
	else if (m_animated && !m_loopable)
	{
		m_srcRect.x = m_srcRect.w * static_cast<int>((SDL_GetTicks() / m_speed));
	}

	m_srcRect.y = m_animIndex * m_transformComponent->height;

	m_dstRect.x = static_cast<int>(m_transformComponent->GetPosition().X());
	m_dstRect.y = static_cast<int>(m_transformComponent->GetPosition().Y());
	m_dstRect.w = TILESIZE;
	m_dstRect.h = TILESIZE;
}

void SpriteComponent::Draw()
{
	Texture::Draw(m_texture, m_srcRect, m_dstRect, spriteFlip);
}

void SpriteComponent::Play(const char* animName)
{
	m_frames = m_animations[animName].m_frames;
	m_animIndex = m_animations[animName].m_index;
	m_speed = m_animations[animName].m_speed;
}

void SpriteComponent::SetTexture(const char* texPath)
{
	m_texture = Texture::LoadTexture(texPath);
}
