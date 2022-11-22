#pragma once
#include <string>

class GameEngine
{
public:
	GameEngine();
	~GameEngine();

	void Init(const char* windowTitle, int windowWidth, int windowHeight, bool isFullScreen);

	void Run();

	void Update();

	void HandleEvents();

	void Render();

	void Shutdown();

	bool IsActive();
	class GameEngine* GetEngine();

	static class SDL_Renderer* GetRenderer();
	static union SDL_Event event;
	static class Manager manager;
	//inline static class Manager GetManager() { return GameEngine::m_manager; }

private:
	class SDLWrapper* m_sdl = nullptr;
	class Window* m_window = nullptr;
	static class Renderer* m_renderer;
	class Map* m_map = nullptr;

	bool m_isRunning;
	bool m_isActive;

	class GameEngine* m_engine;

	const int FPS = 60;
	const int frameDelay = 1000 / FPS;
};
