#include <SDL.h>
#include "Texture.h"
#include <iostream>
#include "InitError.h"
#include "GameEngine.h"


SDL_Texture* Texture::LoadTexture(const char* filePath)
{
	SDL_Texture* texture = nullptr;
	SDL_Surface* surface = SDL_LoadBMP(filePath);
	if (surface == nullptr)
		throw InitError();
	else
	{
		SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 255, 0, 255));
		texture = SDL_CreateTextureFromSurface(GameEngine::GetRenderer(), surface);
		if (texture == NULL)
			throw InitError();
	}

	SDL_FreeSurface(surface);

	return texture;
}

void Texture::Draw(SDL_Texture* texture, SDL_Rect srcRect, SDL_Rect dstRect, SDL_RendererFlip renderFlip)
{
	SDL_RenderCopyEx(GameEngine::GetRenderer(), texture, &srcRect, &dstRect, NULL, NULL, renderFlip);
}

Texture::~Texture()
{
	SDL_DestroyTexture(texture);
	delete texture;
}
