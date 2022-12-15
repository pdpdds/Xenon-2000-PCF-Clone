#pragma once

class SDL_Renderer;
class Window;

class Renderer
{
public:
	Renderer(Window* window, int index, int flags);

	class SDL_Renderer* GetRenderer();

	~Renderer();

private:
	SDL_Renderer* renderer;
};