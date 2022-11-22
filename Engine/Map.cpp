#include "SDL.h"
#include "SDL_image.h"
#include "Map.h"
#include "Texture.h"
#include "GameEngine.h"

Map::Map()
{
	m_bgTexture = Texture::LoadTexture("../Assets/graphics/galaxy2.bmp");


	SDL_QueryTexture(m_bgTexture, nullptr, nullptr, &mWidth, &mHeight);

	//LoadMap(m_lvl);

	/*m_srcRect.x = m_srcRect.y = 0;
	m_srcRect.w = m_dstRect.w = TILESIZE;
	m_srcRect.h = m_dstRect.h = TILESIZE;

	m_dstRect.x = m_dstRect.y = 0;*/
}

Map::~Map()
{
	SDL_DestroyTexture(m_bgTexture);
}

//void Map::LoadMap(int arr[20][25])
//{
//	for (int row = 0; row < 20; ++row)
//	{
//		for (int column = 0; column < 25; ++column)
//		{
//			m_map[row][column] = arr[row][column];
//		}
//	}
//}


void Map::Draw(int x, int y, SDL_Rect* clip)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	//Set clip rendering dimensions
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	SDL_RenderCopy(GameEngine::GetRenderer(), m_bgTexture, clip, &renderQuad);
}

void Map::Update()
{
	//Scroll background
	--scrollingOffset;
	if (scrollingOffset < -mHeight)
	{
		scrollingOffset = 0;
	}
}

void Map::DrawMap()
{
	/*Draw(0, scrollingOffset, nullptr);
	Draw(0, scrollingOffset + mHeight, nullptr);*/
	SDL_RenderCopy(GameEngine::GetRenderer(), m_bgTexture, nullptr, nullptr);

	//Texture::Draw(m_bgTexture, m_srcRect, m_dstRect);
}
