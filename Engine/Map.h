#pragma once

#define TILESIZE 32

class Map
{
public:
	Map();
	~Map();

	void LoadMap();
	void DrawMap();

private:
	class SDL_Rect m_srcRect, m_dstRect;
	class SDL_Texture* m_bgTexture;

	int m_map[20][25];
};