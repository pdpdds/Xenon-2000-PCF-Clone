#include "SDL.h"
#include "GameObject.h"
#include "Texture.h"
#include "GameEngine.h"

GameObject::GameObject(const char* textureSheet, SDL_Renderer* renderer, int x, int y)
{
	m_renderer = renderer;
	m_objectTexture = Texture::LoadTexture(textureSheet);

	m_xPosition = x;
	m_yPosition = y;
}

void GameObject::Update()
{
	m_srcRect.w = 64;
	m_srcRect.h = 64;
	m_srcRect.x = 0;
	m_srcRect.y = 0;

	m_destRect.x = m_xPosition;
	m_destRect.y = m_yPosition;
	m_destRect.w = m_srcRect.w * 2;
	m_destRect.h = m_srcRect.h * 2;
}

void GameObject::Render()
{
	SDL_RenderCopy(m_renderer, m_objectTexture, &m_srcRect, &m_destRect);
}
