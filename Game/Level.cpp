#include <SDL.h>
#include "Level.h"
#include "Texture.h"
#include "GameEngine.h"

Level::Level()
{
	m_bgTexture = Texture::LoadTexture("../Assets/graphics/galaxy2.bmp");


	SDL_QueryTexture(m_bgTexture, nullptr, nullptr, &mWidth, &mHeight);
}

Level::~Level()
{
}

void Level::Draw(int x, int y, SDL_Rect* clip)
{
}

void Level::Update()
{
}

void Level::DrawMap()
{
}
