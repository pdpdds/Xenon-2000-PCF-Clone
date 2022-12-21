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
#include "GroupLabels.h"
#include "Input.h"
#include "LevelManager.h"
#include "../Game/GameManager.h"
#include "World.h"

Renderer* GameEngine::m_renderer = nullptr;
Manager GameEngine::manager;
SDL_Event GameEngine::event;

GameEngine::GameEngine()
{
	m_isRunning = false;
	m_isActive = false;
	m_engine = this;
}

void GameEngine::Init(const char* windowTitle, int windowWidth, int windowHeight, bool isFullScreen)
{
	system("Color 0A");

	//Framerate variables
	frameStart = 0.f;
	currentTime = 0.f;
	frameTime = 0.f;
	deltaTime = 0.f;
	frameRate = 60.f;

	//Generate new random seed every time the engine is initialized
	srand(time(NULL));

	//Used to adjust if window should be full screen
	int flag = 0;

	if (isFullScreen)
	{ 
		flag = SDL_WINDOW_FULLSCREEN;
	}

	//Initialize SDL
	m_sdl = new SDLWrapper(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER);

	//Initialize Window
	m_window = new Window(windowTitle, windowWidth, windowHeight, flag);

	//Initialize Renderer
	GameEngine::m_renderer = new Renderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	m_isActive = true;

	World::GetInstance()->Init();
}

void GameEngine::Run()
{
	m_isRunning = true;

	//Engine Loop
	while (m_isRunning)
	{
		frameStart = currentTime;
		currentTime = SDL_GetTicks();
		deltaTime = (currentTime - frameStart) / 1000.0f;

		frameTime += deltaTime;

		if (frameTime >= (1.0f / frameRate))
		{
			HandleEvents();
			Update();
			frameTime = 0.f;
		}


		World::GetInstance()->Update(deltaTime);

		/*for (int32 i = 0; i < 60; ++i)
		{
			World::GetInstance()->Update(deltaTime)
		}*/

 		Render();
		m_window->updateSurface();
	}

	Shutdown();
}

void GameEngine::Update()
{
	//Refresh and Update Entity Manager
	GameEngine::manager.Refresh();
	GameEngine::manager.Update();

	//Update Game Manager
	GameManager::GetInstance()->Update();
}

void GameEngine::HandleEvents()
{
	//Poll SDL Events
	SDL_PollEvent(&GameEngine::event);

	//Check events
	switch (GameEngine::event.type)
	{
	case SDL_QUIT:
		m_isRunning = false;
		break;
	}

	//Check for Input
	Input::GetInstance()->Listen();
}

void GameEngine::Render()
{
	SDL_SetRenderDrawColor(GameEngine::GetRenderer(), 0, 0, 0, 0);
	SDL_RenderClear(GameEngine::GetRenderer());
	GameEngine::manager.Draw();
	SDL_RenderPresent(GameEngine::GetRenderer());
}

void GameEngine::Shutdown()
{
	SDL_DestroyRenderer(GameEngine::GetRenderer());
	SDL_DestroyWindow(m_window->GetWindow());
	SDL_Quit();

	delete m_window;
	delete m_sdl;
	delete m_renderer;
	delete m_engine;

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

}
