#pragma once

#define TILESIZE 32

class Map
{
public:
	Map();
	~Map();

	void LoadMap();
	void Draw(int x, int y, class SDL_Rect* clip);
	void Update();
	void DrawMap();

	//Image dimensions
	int mWidth;
	int mHeight;

private:
	class SDL_Rect m_srcRect, m_dstRect;
	class SDL_Texture* m_bgTexture;

	//The background scrolling offset
	int scrollingOffset = 0;

	int m_map[20][25];
};