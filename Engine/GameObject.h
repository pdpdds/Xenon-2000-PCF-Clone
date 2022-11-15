#pragma once

class GameObject
{
public:
	GameObject(const char* textureSheet, class SDL_Renderer* renderer, int x, int y);
	~GameObject();

	virtual void Update();
	virtual void Render();

private:
	int m_xPosition;
	int m_yPosition;

	class SDL_Texture* m_objectTexture;

	class SDL_Rect m_srcRect, m_destRect;
	
	class SDL_Renderer* m_renderer;
};