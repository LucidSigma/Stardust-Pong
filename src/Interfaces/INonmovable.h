#pragma once
#ifndef I_NONMOVABLE_H
#define I_NONMOVABLE_H

class INonmovable
{
protected:
	INonmovable() = default;
	~INonmovable() noexcept = default;

	INonmovable(INonmovable&&) noexcept = delete;
	INonmovable& operator =(INonmovable&&) noexcept = default;
};

#endif