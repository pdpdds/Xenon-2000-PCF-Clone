#pragma once

class Renderer
{
public:
	Renderer(class Window* window, int index, int flags);

	class SDL_Renderer* GetRenderer();

	~Renderer();

private:
	class SDL_Renderer* renderer;
};