#include <SDL.h>
#include "SpriteComponent.h"
#include "TransformComponent.h"
#include "Texture.h"
#include "Animation.h"
#include "GameEngine.h"

SpriteComponent::SpriteComponent(const char* texPath)
{
	SetTexture(texPath);
	m_flashTimer = false;
	m_whiteTexture = SDL_CreateTexture(GameEngine::GetRenderer(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 64, 64);
	SDL_SetTextureColorMod(m_whiteTexture, 511, 511, 511);
}

SpriteComponent::SpriteComponent(const char* texPath, bool isAnimated, bool isLoop)
{
	m_animated = isAnimated;
	m_loopable = isLoop;

	Animation m_playerIdle = Animation(0, 1, 1000);
	Animation m_playerTurnRight = Animation(1, 3, 300);

	Animation m_enemyIdle = Animation(0, 4, 200);

	Animation m_droneIdle = Animation(0, 16, 200);

	Animation m_explosion = Animation(0, 10, 95);

	Animation m_pickupIdle = Animation(0, 8, 150);

	m_animations.emplace("PlayerIdle", m_playerIdle);
	m_animations.emplace("PlayerTurnRight", m_playerTurnRight);
	m_animations.emplace("EnemyIdle", m_enemyIdle);
	m_animations.emplace("DroneIdle", m_droneIdle);
	m_animations.emplace("Explosion", m_explosion);
	m_animations.emplace("PickupIdle", m_pickupIdle);

	SetTexture(texPath);
}

SpriteComponent::~SpriteComponent()
{
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
	m_dstRect.w = m_transformComponent->width * 1;
	m_dstRect.h = m_transformComponent->height * 1;
}

void SpriteComponent::Draw()
{
	if (m_flashing)
	{
		//SDL_SetTextureColorMod(m_texture, 194, 116, 107);
		SDL_SetTextureBlendMode(m_texture, SDL_BLENDMODE_ADD);
		SDL_SetTextureBlendMode(m_whiteTexture, SDL_BLENDMODE_MOD);

		Texture::Draw(m_whiteTexture, m_srcRect, m_dstRect, spriteFlip);
	}
	else
	{
		SDL_SetTextureBlendMode(m_texture, SDL_BLENDMODE_BLEND);
		//SDL_SetTextureColorMod(m_texture, 255, 255, 255);
		Texture::Draw(m_texture, m_srcRect, m_dstRect, spriteFlip);
	}
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

void SpriteComponent::SetFlashing(bool flashing)
{
	m_flashing = flashing;
	m_flashTimer = 0;
}
