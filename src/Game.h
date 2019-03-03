#pragma once
#ifndef GAME_H
#define GAME_H

#include "Interfaces/INoncopyable.h"
#include "Interfaces/INonmovable.h"

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "ConfigReader.h"
#include "Renderer.h"
#include "SceneManager.h"
#include "Window.h"

class Game
	: public INoncopyable, public INonmovable
{
private:
	ConfigReader m_configReader;

	Window m_window;
	Renderer m_renderer;

	SceneManager m_sceneManager;
	std::unordered_map<std::string, std::shared_ptr<Scene>> m_scenes;

	bool m_isRunning = false;

	Uint32 m_ticksCount = 0;
	unsigned int m_frameRate = 0;

public:
	Game();
	~Game() noexcept;

	void Play();

	inline const SceneManager& GetSceneManager() const noexcept { return m_sceneManager; }
	inline const Window& GetWindow() const noexcept { return m_window; }

private:
	bool Initialise() noexcept;
	Config ReadConfigFile() noexcept;
	bool InitialiseWindow(const Config& config) noexcept;

	void LoadSceneData() noexcept;

	void PollEvents() noexcept;
	void ProcessInput() noexcept;
	void Update() noexcept;
	void Draw() noexcept;

	void CheckSceneChange() noexcept;

	double CalculateDeltaTime() noexcept;
};

#endif