#pragma once
#ifndef BALL_H
#define BALL_H

#include <glm/glm.hpp>

#include "../Colours.h"
#include "../SDLApplication.h"

struct Ball
{
	static constexpr unsigned int Width = 30;
	static constexpr sdl::Colour Colour = colour::Black;

	glm::vec2 position = glm::vec2(0.0f, 0.0f);
	glm::vec2 velocity = glm::vec2(0.0f, 0.0f);

	sdl::Rectangle GetRectangleFromPosition() const noexcept;
};

#endif