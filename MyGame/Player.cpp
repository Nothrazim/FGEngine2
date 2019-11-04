#include "Player.h"

#include <InputManager.h>
#include <Camera.h>
#include <SDL_render.h>

Player::Player(FG::InputManager* inputManager, FG::Camera* camera) :
	inputManager(inputManager), camera(camera)
{}

void Player::Update(float deltaTime)
{
	MovePlayer(deltaTime);
	MoveCamera(deltaTime);
}

void Player::Render(FG::Camera* const camera)
{
	SDL_Color oldColor = camera->GetColor();
	camera->SetColor({255, 0, 0, 255});

	FG::Vector2D finalPosition = position - camera->position;
	SDL_Rect finalRect{ (int)finalPosition.x, (int)finalPosition.y, 50, 50 };
	SDL_RenderFillRect(camera->GetInternalRenderer(), &finalRect);

	camera->SetColor(oldColor);
}

void Player::MovePlayer(float deltaTime)
{
	FG::Vector2D movement;
	if (inputManager->IsKeyDown(SDL_SCANCODE_A))
	{
		movement.x = -1.0f;
	}

	if (inputManager->IsKeyDown(SDL_SCANCODE_D))
	{
		movement.x = 1.0f;
	}

	if (inputManager->IsKeyDown(SDL_SCANCODE_W))
	{
		movement.y = -1.0f;
	}

	if (inputManager->IsKeyDown(SDL_SCANCODE_S))
	{
		movement.y = 1.0f;
	}

	position += movement * speed * deltaTime;
}

void Player::MoveCamera(float deltaTime)
{
	FG::Vector2D movement;
	if (inputManager->IsKeyDown(SDL_SCANCODE_LEFT))
	{
		movement.x = -1.0f;
	}

	if (inputManager->IsKeyDown(SDL_SCANCODE_RIGHT))
	{
		movement.x = 1.0f;
	}

	if (inputManager->IsKeyDown(SDL_SCANCODE_UP))
	{
		movement.y = -1.0f;
	}

	if (inputManager->IsKeyDown(SDL_SCANCODE_DOWN))
	{
		movement.y = 1.0f;
	}
	camera->position += movement * speed * deltaTime;
}
