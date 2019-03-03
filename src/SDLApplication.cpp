#include "SDLApplication.h"

namespace sdl
{
	void Quit() noexcept
	{
		SDL_Quit();
	}

	std::string GetError() noexcept
	{
		return SDL_GetError();
	}

	bool PollEvent(sdl::Event* sdlEvent) noexcept
	{
		return SDL_PollEvent(sdlEvent) != 0;
	}

	const Uint8* GetKeyboardState() noexcept
	{
		return SDL_GetKeyboardState(nullptr);
	}

	Uint32 GetTicks() noexcept
	{
		return SDL_GetTicks();
	}

	void Delay(Uint32 milliseconds) noexcept
	{
		SDL_Delay(milliseconds);
	}

	bool HasIntersection(const Rectangle& a, const Rectangle& b) noexcept
	{
		return SDL_HasIntersection(&a, &b);
	}

	namespace window
	{
		Window* Create(const std::string& title, int x, int y, int w, int h, Uint32 flags) noexcept
		{
			return SDL_CreateWindow(title.c_str(), x, y, w, h, flags);
		}

		void Destroy(Window* window) noexcept
		{
			SDL_DestroyWindow(window);
		}
	}

	namespace renderer
	{
		Renderer* Create(Window* window, int index, Uint32 flags) noexcept
		{
			return SDL_CreateRenderer(window, index, flags);
		}

		void Destroy(Renderer* renderer) noexcept
		{
			SDL_DestroyRenderer(renderer);
		}

		int SetDrawColour(Renderer* renderer, Uint8 r, Uint8 g, Uint8 b, Uint8 a) noexcept
		{
			return SDL_SetRenderDrawColor(renderer, r, g, b, a);
		}

		void Present(Renderer* renderer) noexcept
		{
			SDL_RenderPresent(renderer);
		}

		int Clear(Renderer* renderer) noexcept
		{
			return SDL_RenderClear(renderer);
		}

		int FillRectangle(Renderer* renderer, const Rectangle* rectangle) noexcept
		{
			return SDL_RenderFillRect(renderer, rectangle);
		}

		int DrawLine(Renderer* renderer, int x1, int y1, int x2, int y2) noexcept
		{
			return SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
		}
	}
}