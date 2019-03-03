#pragma once
#ifndef RENDERER_H
#define RENDERER_H

#include "Interfaces/INoncopyable.h"

#include "Colours.h"
#include "SDLApplication.h"
#include "Window.h"

class Renderer
	: private INoncopyable
{
private:
	static constexpr int s_DefaultIndex = -1;

	struct RendererDestroyer
	{
		void operator ()(sdl::Renderer* renderer) const noexcept;
	};

	std::unique_ptr<sdl::Renderer, RendererDestroyer> m_renderer = nullptr;

public:
	Renderer() noexcept;
	Renderer(const Window& window, int flags, int index = s_DefaultIndex);

	Renderer(Renderer&& other) noexcept;
	Renderer& operator =(Renderer&& other) noexcept;

	~Renderer() noexcept;

	void Destroy() noexcept;

	void Present() const noexcept;
	void DrawRectangle(const sdl::Rectangle& rect, sdl::Colour colour) const noexcept;
	void DrawLine(sdl::Colour colour, int x1, int y1, int x2, int y2) const noexcept;

	void Clear(sdl::Colour colour = colour::Black) const noexcept;

	inline sdl::Renderer* GetPointer() const noexcept { return m_renderer.get(); }

private:
	void ChangeColour(sdl::Colour colour) const noexcept;
};

#endif