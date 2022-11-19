#include "SDL.h"
#include "SpriteComponent.h"
#include "TransformComponent.h"
#include "Texture.h"
#include "Animation.h"

SpriteComponent::SpriteComponent(const char* texPath)
{
	SetTexture(texPath);
}

SpriteComponent::SpriteComponent(const char* texPath, bool isAnimated)
{
	m_animated = isAnimated;

	Animation m_idle = Animation(0, 1, 200);
	Animation m_turnRight = Animation(0, 7, 200);

	m_animations.emplace("Idle", m_idle);
	m_animations.emplace("TurnRight", m_turnRight);
	

	Play("Idle");

	SetTexture(texPath);
}

SpriteComponent::~SpriteComponent()
{
	SDL_DestroyTexture(m_texture);
}

void SpriteComponent::Init()
{
	m_transformComponent = &m_entity->GetComponent<TransformComponent>();

	m_srcRect.x = m_srcRect.y = 0;
	m_srcRect.w = m_transformComponent->width;
	m_srcRect.h = m_transformComponent->height;
}

void SpriteComponent::Update()
{
	if (m_animated)
	{
		m_srcRect.x = m_srcRect.w * static_cast<int>((SDL_GetTicks() / m_speed) % m_frames);
	}

	m_srcRect.y = m_animIndex * m_transformComponent->height;

	m_dstRect.x = static_cast<int>(m_transformComponent->GetPosition().X());
	m_dstRect.y = static_cast<int>(m_transformComponent->GetPosition().Y());
	m_dstRect.w = TILESIZE;
	m_dstRect.h = TILESIZE;
}

void SpriteComponent::Draw()
{
	Texture::Draw(m_texture, m_srcRect, m_dstRect);
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
