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

//Entity& m_player = m_manager.AddEntity();
//Entity& m_player = GameEngine::m_manager.AddEntity();

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

	SDL_GameController* controller{};

	for (int i = 0; i < SDL_NumJoysticks(); ++i) {
		if (SDL_IsGameController(i)) {
			char* mapping;
			std::cout << "Index '" << i << "' is a compatible controller, named '" <<
				SDL_GameControllerNameForIndex(i) << "'" << std::endl;
			controller = SDL_GameControllerOpen(i);
			mapping = SDL_GameControllerMapping(controller);
			std::cout << "Controller " << i << " is mapped as \"" << mapping << std::endl;
			SDL_free(mapping);
		}
		else {
			std::cout << "Index '" << i << "' is not a compatible controller." << std::endl;
		}
	}

	if (controller != NULL)
		SDL_GameControllerClose(controller);


	GameEngine::manager.Init();
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
	//m_map->Update();
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
	/*for (auto& p : players)
	{
		p->Draw();
	}*/
	GameEngine::manager.Draw();
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
