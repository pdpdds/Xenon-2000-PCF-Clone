#pragma once
#include <string>

class SDL_Window;
class SDL_Surface;

class Window
{
public:
	Window(std::string title, int windowWidth, int windowHeight, int flags);

	SDL_Surface* getSurface();

	void updateSurface();

	SDL_Window* GetWindow();

	~Window();
private:
	SDL_Window* window;
};

