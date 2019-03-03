#include "Paddle.h"

sdl::Rectangle Paddle::GetRectangleFromPosition() const noexcept
{
	sdl::Rectangle rectangle
	{
		static_cast<int>(position.x - (Width / 2)),
		static_cast<int>(position.y - (Height / 2)),
		static_cast<int>(Width),
		static_cast<int>(Height)
	};

	return rectangle;
}