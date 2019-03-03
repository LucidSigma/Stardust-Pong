#pragma once
#ifndef SCENE_H
#define SCENE_H

#include <cstdint>

#include "../Renderer.h"

class Game;

class Scene
{
protected:
	Game& m_game;

public:
	Scene(Game& game);
	virtual ~Scene() noexcept = default;

	virtual void Load() noexcept = 0;
	virtual void Unload() noexcept = 0;

	virtual void ProcessInput(const std::uint8_t* keyStates) = 0;
	virtual void Update(double deltaTime) = 0;
	virtual void Draw(const Renderer& renderer) = 0;
};

#endif