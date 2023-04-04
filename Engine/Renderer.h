#pragma once

struct SDL_Renderer;
class Window;

class Renderer
{
public:
	Renderer(Window* window, int index, int flags);

	struct SDL_Renderer* GetRenderer();

	~Renderer();

private:
	SDL_Renderer* renderer;
};