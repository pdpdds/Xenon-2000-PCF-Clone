#pragma once

class Texture
{
public:
	 static class SDL_Texture* LoadTexture(const char* filePath);
	 static void Draw(class SDL_Texture* texture, class SDL_Rect srcRect, class SDL_Rect dstRect);

	~Texture();

private:
	 class SDL_Texture* texture;
};
