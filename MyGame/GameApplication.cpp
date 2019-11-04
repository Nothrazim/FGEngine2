#include <Window.h>
#include <InputManager.h>
#include <Camera.h>
#include <EntityManager.h>

#include <Logger.h>
#include <SDL.h>

#include "GameApplication.h"
#include "Player.h"

bool GameApplication::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		FG::Logger::Log(SDL_GetError(), FG::Logger::RemovePathFromFile(__FILE__), __LINE__);
		return false;
	}

	window = new FG::Window();
	if (!window->Initialize("My game", 1024, 768))
	{
		FG::Logger::Log(SDL_GetError(), FG::Logger::RemovePathFromFile(__FILE__), __LINE__);
		return false;
	}

	inputManager = new FG::InputManager();
	inputManager->Initialize();

	camera = new FG::Camera();
	if (camera->Initialize(window))
	{ return false; }

	entityManager = new FG::EntityManager();

	Player* player = new Player(inputManager, camera);
	entityManager->AddEntity(player);

	return true;
}

void GameApplication::Run()
{
	bool quit = false;
	while(!quit)
	{
		time.StartFrame();
		inputManager->Update(quit);
		entityManager->Update(time.DeltaTime());
		camera->StartRenderFrame();
		entityManager->Render(camera);
		camera->EndRenderFrame();
		time.EndFrame();
	}
}

void GameApplication::Shutdown()
{
	if (entityManager)
	{
		entityManager->Shutdown();
		delete entityManager;
		entityManager = nullptr;
	}
	if (camera)
	{
		camera->Shutdown();
		delete camera;
		camera = nullptr;
	}
	if (inputManager)
	{
		delete inputManager;
		inputManager = nullptr;
	}
	if (window)
	{
		window->Shutdown();
		delete window;
		window = nullptr;
	}
	SDL_Quit();
}
