#pragma once

#define TILESIZE 32

class SDL_Rect;

class Level
{
public:
	Level();
	~Level();

	void Draw(int x, int y, SDL_Rect* clip);
	void Update();
	void DrawMap();

	//Image dimensions
	int mWidth;
	int mHeight;

private:
	SDL_Rect m_srcRect, m_dstRect;
	class SDL_Texture* m_bgTexture;

	//The background scrolling offset
	int scrollingOffset = 0;

};