#include "SceneManager.h"

#include "Scenes/Scene.h"

SceneManager::~SceneManager() noexcept
{
	if (m_currentScene != nullptr)
	{
		m_currentScene->Unload();
		m_currentScene = nullptr;
	}
}

void SceneManager::ChangeScene(const std::shared_ptr<Scene>& newScene) noexcept
{
	if (m_currentScene != nullptr)
	{
		m_currentScene->Unload();
	}
	
	m_currentScene = newScene;
	m_currentScene->Load();

	m_nextScenePending = "";
}

void SceneManager::ProcessCurrentSceneInput(const std::uint8_t* keyStates)
{
	if (m_currentScene != nullptr)
	{
		m_currentScene->ProcessInput(keyStates);
	}
}

void SceneManager::UpdateCurrentScene(double deltaTime)
{
	if (m_currentScene != nullptr)
	{
		m_currentScene->Update(deltaTime);
	}
}

void SceneManager::DrawCurrentScene(const Renderer& renderer)
{
	if (m_currentScene != nullptr)
	{
		m_currentScene->Draw(renderer);
	}
}