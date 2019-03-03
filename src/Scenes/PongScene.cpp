#include "PongScene.h"

#include <algorithm>

#include "../Game.h"
#include "../Random.h"

PongScene::PongScene(Game& game)
	: Scene(game), m_initialBallPosition(m_game.GetWindow().GetWidth() / 2, m_game.GetWindow().GetHeight() / 2)
{
	m_walls.emplace_back(sdl::Rectangle
		{
			0,
			0,
			static_cast<int>(m_game.GetWindow().GetWidth()),
			static_cast<int>(Wall::Thickness)
		}
	);

	m_walls.emplace_back(sdl::Rectangle
		{
			0,
			static_cast<int>(m_game.GetWindow().GetHeight() - Wall::Thickness),
			static_cast<int>(m_game.GetWindow().GetWidth()),
			static_cast<int>(m_game.GetWindow().GetHeight())
		}
	);

	m_ball.position = m_initialBallPosition;
	SetRandomBallVelocities();

	m_leftPaddle.position.x = s_PaddleOffset;
	m_leftPaddle.position.y = static_cast<float>(m_game.GetWindow().GetHeight() / 2);

	m_rightPaddle.position.x = static_cast<float>(m_game.GetWindow().GetWidth() - s_PaddleOffset);
	m_rightPaddle.position.y = static_cast<float>(m_game.GetWindow().GetHeight() / 2);
}

void PongScene::Load() noexcept
{ }

void PongScene::Unload() noexcept
{ }

void PongScene::ProcessInput(const std::uint8_t* keyStates)
{
	m_leftPaddleDirection = 0;
	m_rightPaddleDirection = 0;

	if (keyStates[s_LeftPaddleUp])
	{
		m_leftPaddleDirection--;
	}

	if (keyStates[s_LeftPaddleDown])
	{
		m_leftPaddleDirection++;
	}

	if (keyStates[s_RightPaddleUp])
	{
		m_rightPaddleDirection--;
	}

	if (keyStates[s_RightPaddleDown])
	{
		m_rightPaddleDirection++;
	}
}

void PongScene::Update(double deltaTime)
{
	m_leftPaddle.position.y += Paddle::yVelocity * m_leftPaddleDirection * static_cast<float>(deltaTime);
	m_leftPaddle.position.y = std::clamp(m_leftPaddle.position.y, static_cast<float>(Paddle::Height / 2 + Wall::Thickness), static_cast<float>(m_game.GetWindow().GetHeight() - Paddle::Height / 2 - Wall::Thickness));

	m_rightPaddle.position.y += Paddle::yVelocity * m_rightPaddleDirection * static_cast<float>(deltaTime);
	m_rightPaddle.position.y = std::clamp(m_rightPaddle.position.y, static_cast<float>(Paddle::Height / 2 + Wall::Thickness), static_cast<float>(m_game.GetWindow().GetHeight() - Paddle::Height / 2 - Wall::Thickness));

	m_ball.position += m_ball.velocity * static_cast<float>(deltaTime);

	if ((m_ball.position.y - Ball::Width / 2) < Wall::Thickness && m_ball.velocity.y < 0)
	{
		m_ball.position.y = Wall::Thickness + Ball::Width / 2;
		m_ball.velocity.y *= -1;
	}

	if ((m_ball.position.y + Ball::Width / 2) > m_game.GetWindow().GetHeight() - Wall::Thickness && m_ball.velocity.y > 0)
	{
		m_ball.position.y = static_cast<float>(m_game.GetWindow().GetHeight() - Wall::Thickness - Ball::Width / 2);
		m_ball.velocity.y *= -1;
	}

	if (sdl::HasIntersection(m_ball.GetRectangleFromPosition(), m_leftPaddle.GetRectangleFromPosition())
		|| sdl::HasIntersection(m_ball.GetRectangleFromPosition(), m_rightPaddle.GetRectangleFromPosition()))
	{
		m_ball.velocity.x *= -1;
	}

	if ((m_ball.position.x + Ball::Width / 2) < 0 || (m_ball.position.x - Ball::Width / 2) > m_game.GetWindow().GetWidth())
	{
		m_ball.position = m_initialBallPosition;
		SetRandomBallVelocities();
	}
}

void PongScene::Draw(const Renderer& renderer)
{
	renderer.Clear(s_BackgroundColour);

	for (const auto& wall : m_walls)
	{
		renderer.DrawRectangle(wall.rectangle, Wall::Colour);
	}

	renderer.DrawRectangle(m_ball.GetRectangleFromPosition(), Ball::Colour);

	renderer.DrawRectangle(m_leftPaddle.GetRectangleFromPosition(), Paddle::Colour);
	renderer.DrawRectangle(m_rightPaddle.GetRectangleFromPosition(), Paddle::Colour);
}

void PongScene::SetRandomBallVelocities()
{
	short initialXDirection = Random::GetInt(0, 1) ? 1 : -1;
	short initialYDirection = Random::GetInt(0, 1) ? 1 : -1;

	m_ball.velocity = glm::vec2(s_BallXVelocity * initialXDirection, s_BallYVelocity * initialYDirection);
}