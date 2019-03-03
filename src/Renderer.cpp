#include "Renderer.h"

#include <stdexcept>
#include <utility>

void Renderer::RendererDestroyer::operator ()(sdl::Renderer* renderer) const noexcept
{
	sdl::renderer::Destroy(renderer);
}

Renderer::Renderer() noexcept
	: m_renderer(nullptr)
{ }

Renderer::Renderer(const Window& window, int flags, int index)
	: m_renderer(sdl::renderer::Create(window.GetPointer(), index, flags))
{
	if (m_renderer == nullptr)
	{
		SDL_Log("Failed to create renderer: %s", sdl::GetError());

		throw std::runtime_error("SDL failed to create renderer.");
	}
}

Renderer::Renderer(Renderer&& other) noexcept
	: m_renderer(nullptr)
{
	std::swap(this->m_renderer, other.m_renderer);
}

Renderer& Renderer::operator =(Renderer&& other) noexcept
{
	this->m_renderer = std::exchange(other.m_renderer, nullptr);

	return *this;
}

Renderer::~Renderer() noexcept
{
	Destroy();
}

void Renderer::Destroy() noexcept
{
	m_renderer = nullptr;
}

void Renderer::Present() const noexcept
{
	sdl::renderer::Present(GetPointer());
}

void Renderer::DrawRectangle(const sdl::Rectangle& rect, sdl::Colour colour) const noexcept
{
	ChangeColour(colour);
	sdl::renderer::FillRectangle(GetPointer(), &rect);
}

void Renderer::DrawLine(sdl::Colour colour, int x1, int y1, int x2, int y2) const noexcept
{
	ChangeColour(colour);
	sdl::renderer::DrawLine(GetPointer(), x1, y1, x2, y2);
}

void Renderer::Clear(sdl::Colour colour) const noexcept
{
	ChangeColour(colour);
	sdl::renderer::Clear(GetPointer());
}

void Renderer::ChangeColour(sdl::Colour colour) const noexcept
{
	sdl::renderer::SetDrawColour(GetPointer(), colour.r, colour.g, colour.b, colour.a);
}