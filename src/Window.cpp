#include "Window.h"

#include <stdexcept>
#include <utility>

void Window::WindowDestroyer::operator ()(sdl::Window* window) const noexcept
{
	sdl::window::Destroy(window);
}

Window::Window() noexcept
{ }

Window::Window(const std::string& title, const sdl::Rectangle& rect, unsigned int flags)
	: m_window(sdl::window::Create(title.c_str(), rect.x, rect.y, rect.w, rect.h, flags)), m_width(rect.w), m_height(rect.h)
{
	if (m_window == nullptr)
	{
		SDL_Log("Failed to create window: %s", sdl::GetError());

		throw std::runtime_error("SDL failed to create window.");
	}
}

Window::Window(Window&& other) noexcept
	: m_window(nullptr), m_width(other.m_width), m_height(other.m_height)
{
	std::swap(this->m_window, other.m_window);

	other.m_width = 0;
	other.m_height = 0;
}

Window& Window::operator =(Window&& other) noexcept
{
	this->m_window = std::exchange(other.m_window, nullptr);
	this->m_width = std::exchange(other.m_width, 0);
	this->m_height = std::exchange(other.m_height, 0);

	return *this;
}

Window::~Window() noexcept
{
	Destroy();
}

void Window::Destroy() noexcept
{
	this->m_window = nullptr;
}