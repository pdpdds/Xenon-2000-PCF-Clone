#include "SDL.h"
#include "SpriteComponent.h"
#include "TransformComponent.h"
#include "Texture.h"

SpriteComponent::SpriteComponent(const char* texPath)
{
	SetTexture(texPath);
}

void SpriteComponent::Init()
{
	m_transformComponent = &m_entity->GetComponent<TransformComponent>();

	m_srcRect.x = m_srcRect.y = 0;
	m_srcRect.w = m_srcRect.h = TILESIZE;
	m_dstRect.w = m_dstRect.h = TILESIZE;
}

void SpriteComponent::Update()
{
	m_dstRect.x = (int)m_transformComponent->GetPosition().X();
	m_dstRect.y = (int)m_transformComponent->GetPosition().Y();
}

void SpriteComponent::Draw()
{
	Texture::Draw(m_texture, m_srcRect, m_dstRect);
}

void SpriteComponent::SetTexture(const char* texPath)
{
	m_texture = Texture::LoadTexture(texPath);
}
