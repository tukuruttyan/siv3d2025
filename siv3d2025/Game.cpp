#include "Game.h"
#include "TitleScene.h"

namespace GameCore
{
	Game::Game()
		: m_sceneGroup([this](const std::type_index& changeSceneType) { ChangeScene(changeSceneType); })
	{
		ChangeScene(typeid(TitleScene));
	}

	void Game::RunAsync()
	{
		while (System::Update())
		{
			m_currentScene->Update();
		}
	}

	void Game::ChangeScene(const std::type_index& typeIndex)
	{
		if (m_currentScene)
		{
			m_currentScene->OnExit();
		}
		m_currentScene = m_sceneGroup.Catch(typeIndex);
		if (m_currentScene)
		{
			m_currentScene->OnEnter();
		}
	}
}
