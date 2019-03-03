#pragma once
#ifndef PADDLE_H
#define PADDLE_H

#include <glm/glm.hpp>

#include "../Colours.h"
#include "../SDLApplication.h"

struct Paddle
{
	static constexpr unsigned int Width = 20;
	static constexpr unsigned int Height = 150;

	static constexpr float yVelocity = 300.0f;

	static constexpr sdl::Colour Colour = colour::Yellow;

	glm::vec2 position;

	sdl::Rectangle GetRectangleFromPosition() const noexcept;
};

#endif