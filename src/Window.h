#pragma once
#ifndef WINDOW_H
#define WINDOW_H

#include "Interfaces/INoncopyable.h"

#include <memory>
#include <string>

#include "SDLApplication.h"

class Window
	: private INoncopyable
{
private:
	struct WindowDestroyer
	{
		void operator ()(sdl::Window* window) const noexcept;
	};

	std::unique_ptr<sdl::Window, WindowDestroyer> m_window = nullptr;

	unsigned int m_width = 0;
	unsigned int m_height = 0;

public:
	Window() noexcept;
	Window(const std::string& title, const sdl::Rectangle& rect, unsigned int flags = SDL_WINDOW_SHOWN);

	Window(Window&& other) noexcept;
	Window& operator =(Window&& other) noexcept;

	~Window() noexcept;

	void Destroy() noexcept;

	inline sdl::Window* GetPointer() const noexcept { return m_window.get(); }
	inline unsigned int GetWidth() const noexcept { return m_width; }
	inline unsigned int GetHeight() const noexcept { return m_height; }
};

#endif