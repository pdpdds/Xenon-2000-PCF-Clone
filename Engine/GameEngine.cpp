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
#include "Pawn.h"
#include "GroupLabels.h"

Renderer* GameEngine::m_renderer = nullptr;
Manager GameEngine::manager;
SDL_Event GameEngine::event;
SDL_GameController* controller = nullptr;

auto& players(GameEngine::manager.GetGroup(Groups::GROUP_PLAYERS));

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

	
	m_sdl = new SDLWrapper(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER);

	m_window = new Window(windowTitle, windowWidth, windowHeight, flag);

	GameEngine::m_renderer = new Renderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	m_isActive = true;
		
	if (SDL_Init(SDL_INIT_GAMECONTROLLER) < 0)
	{
		std::cout << "ERROR: Game Controller failed to initialize" << std::endl;
		throw InitError();
	}
	if (SDL_NumJoysticks() < 1)
	{
		std::cout << "WARNING: No Gamepad detected" << std::endl;
	}
	else
	{
		controller = SDL_GameControllerOpen(0);	
	}

	/*for (auto& p : players)
	{
		p->Init();
	}*/
}

void GameEngine::Run()
{
	m_map = new Map();

	Pawn* pawn = new Pawn();

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
	GameEngine::manager.Refresh();
	GameEngine::manager.Update();
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
	//Render all active players
	for (auto& p : players)
	{
		p->Draw();
	}
	//GameEngine::manager.Draw();
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
