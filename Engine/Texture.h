#pragma once

#include <SDL.h>

class SDL_Texture;
class SDL_Rect;

class Texture
{
public:
	 static SDL_Texture* LoadTexture(const char* filePath);
	 static void Draw(SDL_Texture* texture, SDL_Rect srcRect, SDL_Rect dstRect, SDL_RendererFlip renderFlip);

	~Texture();

private:
	 SDL_Texture* texture;
};
