#include <SDL.h>
#include "GameEngine.h"
#include "SDLWrapper.h"
#include "Window.h"
#include "Renderer.h"
#include "Texture.h"
#include <iostream>
#include <stdlib.h>
#include "Map.h"
#include "Components.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "PlayerController.h"

Renderer* GameEngine::m_renderer = nullptr;

Manager m_manager;
SDL_Event GameEngine::event;
auto& m_player(m_manager.AddEntity());


GameEngine::GameEngine()
{
	m_isRunning = false;
	m_isActive = false;
	m_engine = this;
}

void GameEngine::Init(const char* windowTitle, int windowWidth, int windowHeight, bool isFullScreen)
{
	system("Color 0A");

	//Used to adjust if window should be full screen
	int flag = 0;

	if (isFullScreen)
	{ 
		flag = SDL_WINDOW_FULLSCREEN;
	}
	
	m_sdl = new SDLWrapper(SDL_INIT_VIDEO | SDL_INIT_TIMER);

	m_window = new Window(windowTitle, windowWidth, windowHeight, flag);

	GameEngine::m_renderer = new Renderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	m_isActive = true;
	
	m_map = new Map();

	m_player.AddComponent<TransformComponent>(0, 0);
	m_player.AddComponent<SpriteComponent>("../Assets/graphics/Ship1.bmp");
	m_player.AddComponent<PlayerController>();
	//m_player.AddComponent<KeyboardController>();
}

void GameEngine::Run()
{
	Uint32 frameStart;
	int frameTime;

	m_isRunning = true;

	while (m_isRunning)
	{
		frameStart = SDL_GetTicks();
		
		HandleEvents();
		Update();
		Render();
		m_window->updateSurface();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}

	Shutdown();
}

void GameEngine::Update()
{
	m_manager.Refresh();
	m_manager.Update();
}

void GameEngine::HandleEvents()
{
	SDL_PollEvent(&GameEngine::event);

	//Check events
	switch (GameEngine::event.type)
	{
	case SDL_QUIT:
		m_isRunning = false;
		break;
	default:
		break;
	}
}

void GameEngine::Render()
{
	SDL_SetRenderDrawColor(GameEngine::GetRenderer(), 0, 0, 0, 0);
	SDL_RenderClear(GameEngine::GetRenderer());
	m_map->DrawMap(); 
	m_manager.Draw();
	SDL_RenderPresent(GameEngine::GetRenderer());
}

void GameEngine::Shutdown()
{
	SDL_DestroyRenderer(GameEngine::GetRenderer());
	SDL_DestroyWindow(m_window->GetWindow());
	SDL_Quit();

	std::cout << "Engine shutdown" << std::endl;
}

bool GameEngine::IsActive()
{
	return m_isActive;
}

GameEngine* GameEngine::GetEngine()
{
	return m_engine;
}

SDL_Renderer* GameEngine::GetRenderer()
{
	return m_renderer->GetRenderer();
}

GameEngine::~GameEngine()
{
	delete m_window;
	delete m_sdl;
}