#pragma once
#include <string>
class Window
{
public:
	Window(std::string title, int windowWidth, int windowHeight, int flags);

	class SDL_Surface* getSurface();

	void updateSurface();

	class SDL_Window* GetWindow();

	~Window();
private:
	class SDL_Window* window;
};

