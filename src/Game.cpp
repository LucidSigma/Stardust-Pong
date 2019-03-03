#include "Game.h"

#ifdef _DEBUG
#include <algorithm>
#endif

#include <iterator>

#include "Scenes/PongScene.h"

Game::Game()
{
	if (!Initialise())
	{
		throw std::runtime_error("Game could not be created.");
	}
}

Game::~Game() noexcept
{
	sdl::Quit();
}

void Game::Play()
{
	while (m_isRunning)
	{
		PollEvents();
		ProcessInput();
		Update();
		Draw();

		CheckSceneChange();
	}
}

bool Game::Initialise() noexcept
{
	if (!sdl::Initialise(SDL_INIT_VIDEO))
	{
		return false;
	}

	Config config;

	try
	{
		config = ReadConfigFile();
	}
	catch (const std::runtime_error&)
	{
		return false;
	}

	if (!InitialiseWindow(config))
	{
		return false;
	}

	m_frameRate = config.frameRate;
	m_isRunning = true;

	LoadSceneData();

	return true;
}

Config Game::ReadConfigFile() noexcept
{
	return m_configReader.ReadConfigFile();
}

bool Game::InitialiseWindow(const Config& config) noexcept
{
	try
	{
		sdl::Rectangle windowPosition
		{
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			static_cast<int>(config.windowWidth),
			static_cast<int>(config.windowHeight)
		};

		m_window = Window(config.title, windowPosition);

		int rendererFlags = SDL_RENDERER_ACCELERATED;

		if (config.enableVsync)
		{
			rendererFlags |= SDL_RENDERER_PRESENTVSYNC;
		}

		m_renderer = Renderer(m_window, rendererFlags);
	}
	catch (const std::runtime_error&)
	{
		return false;
	}

	return true;
}

void Game::LoadSceneData() noexcept
{
	std::shared_ptr<Scene> pongScene = std::make_shared<PongScene>(*this);
	m_scenes.emplace("Pong", pongScene);

	m_sceneManager.ChangeScene(pongScene);
}

void Game::PollEvents() noexcept
{
	sdl::Event gameEvent;

	while (sdl::PollEvent(&gameEvent))
	{
		switch (gameEvent.type)
		{
		case SDL_KEYDOWN:
			if (gameEvent.key.keysym.sym == SDLK_ESCAPE)
			{
				m_isRunning = false;
			}

			break;

		case SDL_QUIT:
			m_isRunning = false;

			break;

		default:
			break;
		}
	}
}

void Game::ProcessInput() noexcept
{
	const Uint8* keyStates = sdl::GetKeyboardState();
	m_sceneManager.ProcessCurrentSceneInput(keyStates);
}

void Game::Update() noexcept
{
	double deltaTime = CalculateDeltaTime();
	m_sceneManager.UpdateCurrentScene(deltaTime);
}

void Game::Draw() noexcept
{
	m_sceneManager.DrawCurrentScene(m_renderer);
	m_renderer.Present();
}

void Game::CheckSceneChange() noexcept
{
	if (!m_sceneManager.GetNextScenePending().empty())
	{
		if (m_scenes.find(m_sceneManager.GetNextScenePending()) != std::end(m_scenes))
		{
			m_sceneManager.ChangeScene(m_scenes[m_sceneManager.GetNextScenePending()]);
		}
	}
}

double Game::CalculateDeltaTime() noexcept
{
	static constexpr double MillisecondsPerSecond = 1000.0;
	double deltaTime = 0.0;

	if (m_frameRate > 0)
	{
		static const double millisecondsPerFrame = MillisecondsPerSecond / m_frameRate;
		double deltaTicks = static_cast<double>(sdl::GetTicks() - m_ticksCount);

		if (deltaTicks < millisecondsPerFrame)
		{
			sdl::Delay(static_cast<Uint32>(millisecondsPerFrame - deltaTicks));
		}

		deltaTime = deltaTicks / MillisecondsPerSecond;
	}
	else
	{
		deltaTime = static_cast<double>(sdl::GetTicks() - m_ticksCount) / MillisecondsPerSecond;
	}

#ifdef _DEBUG
	static constexpr double DeltaTimeMax = 0.05;
	deltaTime = std::min(deltaTime, DeltaTimeMax);
#endif

	m_ticksCount = sdl::GetTicks();

	return deltaTime;
}