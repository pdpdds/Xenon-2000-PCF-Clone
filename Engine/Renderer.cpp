#include <SDL.h>
#include "Renderer.h"
#include "InitError.h"
#include "Window.h"
#include <iostream>


Renderer::Renderer(Window* window, int index, int flags)
{
	renderer = SDL_CreateRenderer(window->GetWindow(), index, flags);
	if (renderer == nullptr)
	{
		throw InitError();
	}
	else if (renderer)
	{
		std::cout << "Render Initialized" << std::endl;
	}
}

SDL_Renderer* Renderer::GetRenderer()
{
	return renderer;
}

Renderer::~Renderer()
{
	SDL_DestroyRenderer(renderer);
}
