#pragma once
#ifndef PONG_SCENE_H
#define PONG_SCENE_H

#include "Scene.h"

#include <glm/glm.hpp>

#include <vector>

#include "../SDLApplication.h"
#include "../Objects/Ball.h"
#include "../Objects/Paddle.h"
#include "../Objects/Wall.h"

class Game;

class PongScene final
	: public Scene
{
private:
	static constexpr float s_BallXVelocity = 450.0f;
	static constexpr float s_BallYVelocity = 400.0f;

	static constexpr unsigned int s_PaddleOffset = 30;

	static constexpr sdl::Colour s_BackgroundColour { 0x80, 0x00, 0x80, 0xFF };

	static constexpr int s_LeftPaddleUp = SDL_SCANCODE_W;
	static constexpr int s_LeftPaddleDown = SDL_SCANCODE_S;
	static constexpr int s_RightPaddleUp = SDL_SCANCODE_UP;
	static constexpr int s_RightPaddleDown = SDL_SCANCODE_DOWN;

	const glm::vec2 m_initialBallPosition;

	std::vector<Wall> m_walls;
	Ball m_ball;

	Paddle m_leftPaddle;
	short m_leftPaddleDirection = 0;

	Paddle m_rightPaddle;
	short m_rightPaddleDirection = 0;

public:
	PongScene(Game& game);
	virtual ~PongScene() override = default;

	virtual void Load() noexcept override;
	virtual void Unload() noexcept override;

	virtual void ProcessInput(const std::uint8_t* keyStates) override;
	virtual void Update(double deltaTime) override;
	virtual void Draw(const Renderer& renderer) override;

private:
	void SetRandomBallVelocities();
};

#endif