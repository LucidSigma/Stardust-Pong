#pragma once
#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include <cstdint>
#include <memory>
#include <string>

#include "Renderer.h"

class Scene;

class SceneManager
{
private:
	std::shared_ptr<Scene> m_currentScene = nullptr;
	mutable std::string m_nextScenePending = "";

public:
	SceneManager() = default;
	~SceneManager() noexcept;

	void ChangeScene(const std::shared_ptr<Scene>& newScene) noexcept;

	void ProcessCurrentSceneInput(const std::uint8_t* keyStates);
	void UpdateCurrentScene(double deltaTime);
	void DrawCurrentScene(const Renderer& renderer);

	inline const std::string& GetNextScenePending() const noexcept { return m_nextScenePending; }
	inline void SetNextScenePending(const std::string& sceneName) const noexcept { m_nextScenePending = sceneName; }
};

#endif