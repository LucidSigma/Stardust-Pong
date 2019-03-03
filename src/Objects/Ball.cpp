#include "Ball.h"

sdl::Rectangle Ball::GetRectangleFromPosition() const noexcept
{
	sdl::Rectangle rectangle
	{
		static_cast<int>(position.x - (Width / 2)),
		static_cast<int>(position.y - (Width / 2)),
		static_cast<int>(Width),
		static_cast<int>(Width)
	};

	return rectangle;
}