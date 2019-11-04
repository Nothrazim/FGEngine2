#pragma once

#include <Entity.h>
#include <Vector2D.h>

namespace FG
{
	class Window;
	class InputManager;
	class Camera;
}

class Player : public FG::Entity
{
public:
	float speed = 100.0f;
	
	Player(FG::InputManager* inputManager, FG::Camera* camera);

	void Update(float deltaTime) override;
	void Render(FG::Camera* const camera) override;
	
private:
	FG::InputManager* inputManager = nullptr;
	FG::Camera* camera = nullptr;

	FG::Vector2D position;

	Player() {}

	void MovePlayer(float deltaTime);
	void MoveCamera(float deltaTime);
};
