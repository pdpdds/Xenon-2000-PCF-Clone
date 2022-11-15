#include <SDL.h>
#include "Window.h"
#include "InitError.h"
#include <iostream>

Window::Window(std::string title, int windowWidth, int windowHeight, int flags)
{
	window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, flags);
	if (window == nullptr)
	{
		throw InitError();
	}
	else if (window)
	{
		std::cout << "Window Created" << std::endl;
	}

}

SDL_Surface* Window::getSurface()
{
	return SDL_GetWindowSurface(window);
}

void Window::updateSurface()
{
	SDL_UpdateWindowSurface(window);
}

SDL_Window* Window::GetWindow()
{
	return window;
}

Window::~Window()
{
	SDL_DestroyWindow(window);
}
