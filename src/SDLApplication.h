#pragma once
#ifndef SDL_APPLICATION_H
#define SDL_APPLICATION_H

#include <SDL2/SDL.h>

#include <string>
#include <type_traits>

namespace sdl
{
	using Colour = SDL_Color;
	using Event = SDL_Event;
	using Rectangle = SDL_Rect;
	using Renderer = SDL_Renderer;
	using Window = SDL_Window;

	template <typename... Args, typename = std::enable_if_t<(std::is_same_v<decltype(SDL_INIT_VIDEO), Args> && ...) && (sizeof...(Args) > 0)>>
	bool Initialise(Args&&... flags) noexcept
	{
		if (SDL_Init((flags | ...)) != 0)
		{
			SDL_Log("Unable to initialise SDL: %s", SDL_GetError());

			return false;
		}

		return true;
	}

	extern void Quit() noexcept;

	extern std::string GetError() noexcept;
	extern bool PollEvent(sdl::Event* event) noexcept;

	extern const Uint8* GetKeyboardState() noexcept;

	extern Uint32 GetTicks() noexcept;
	extern void Delay(Uint32 milliseconds) noexcept;

	extern bool HasIntersection(const Rectangle& a, const Rectangle& b) noexcept;

	namespace window
	{
		extern Window* Create(const std::string& title, int x, int y, int w, int h, Uint32 flags) noexcept;
		extern void Destroy(Window* window) noexcept;
	}

	namespace renderer
	{
		extern Renderer* Create(Window* window, int index, Uint32 flags) noexcept;
		extern void Destroy(Renderer* renderer) noexcept;

		extern int SetDrawColour(Renderer* renderer, Uint8 r, Uint8 g, Uint8 b, Uint8 a) noexcept;

		extern void Present(Renderer* renderer) noexcept;
		extern int Clear(Renderer* renderer) noexcept;
		extern int FillRectangle(Renderer* renderer, const Rectangle* rectangle) noexcept;
		extern int DrawLine(Renderer* renderer, int x1, int y1, int x2, int y2) noexcept;
	}
}

#endif