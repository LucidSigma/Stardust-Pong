#pragma once
#ifndef RANDOM_H
#define RANDOM_H

#include <random>
#include <type_traits>

class Random
{
private:
	inline static std::random_device s_randomSeeder;
	inline static std::mt19937 s_randomEngine = std::mt19937(s_randomSeeder());

public:
	Random() = delete;
	~Random() noexcept = delete;

	template <typename T = float, typename = std::enable_if_t<std::is_floating_point_v<T>>>
	static T GetFloat(T min, T max) noexcept
	{
		std::uniform_real_distribution<T> randomRange(min, max);

		return randomRange(s_randomEngine);
	}

	template <typename T = int, typename = std::enable_if_t<std::is_integral_v<T>>>
	static T GetInt(T min, T max) noexcept
	{
		std::uniform_int_distribution<T> randomRange(min, max);

		return randomRange(s_randomEngine);
	}
};

#endif