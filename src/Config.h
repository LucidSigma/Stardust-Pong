#pragma once
#ifndef CONFIG_H
#define CONFIG_H

#include <string>

struct Config
{
	std::string title;

	unsigned int windowWidth;
	unsigned int windowHeight;
	unsigned int frameRate;

	bool enableVsync;
};

#endif