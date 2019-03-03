#pragma	once
#ifndef COLOURS_H
#define COLOURS_H

#include "SDLApplication.h"

namespace colour
{
	static constexpr sdl::Colour Black { 0x00, 0x00, 0x00, 0xFF };
	static constexpr sdl::Colour Red { 0xFF, 0x00, 0x00, 0xFF };
	static constexpr sdl::Colour Green { 0x00, 0xFF, 0x00, 0xFF };
	static constexpr sdl::Colour Blue { 0x00, 0x00, 0xFF, 0xFF };
	static constexpr sdl::Colour Yellow { 0xFF, 0xFF, 0x00, 0xFF };
	static constexpr sdl::Colour Magenta { 0xFF, 0x00, 0xFF, 0xFF };
	static constexpr sdl::Colour Cyan { 0x00, 0xFF, 0xFF, 0xFF };
	static constexpr sdl::Colour White { 0xFF, 0xFF, 0xFF, 0xFF };
}

#endif