#pragma once
#ifndef WALL_H
#define WALL_H

#include "../Colours.h"
#include "../SDLApplication.h"

struct Wall
{
	static constexpr unsigned int Thickness = 25;
	static constexpr sdl::Colour Colour = colour::White;

	sdl::Rectangle rectangle;

	explicit Wall(const sdl::Rectangle& rectangle);
};

#endif