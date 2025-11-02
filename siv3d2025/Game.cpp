#include "Game.h"
#include "TitleScene.h"

namespace GameCore
{
	Game::Game()
		: m_sceneGroup([this](const std::type_index& changeSceneType) { OnChangeScene(changeSceneType); })
	{
		OnChangeScene(typeid(TitleScene));
	}

	void Game::RunAsync()
	{
		while (System::Update())
		{
			m_currentScene->Update();
			if (SimpleGUI::Button(U"Licenses", Vec2{ 40, 40 }))
			{
				// Web ブラウザでライセンス情報を表示する
				LicenseManager::ShowInBrowser();
			}
		}
	}

	void Game::OnChangeScene(const std::type_index& typeIndex)
	{
		if (m_currentScene)
		{
			m_currentScene->OnExit();
		}
		m_currentScene = m_sceneGroup.Catch(typeIndex);
		if (!m_currentScene)
		{
			throw std::runtime_error("Scene not found: typeIndex is invalid or unregistered.");
		}
		if (m_currentScene)
		{
			m_currentScene->OnEnter();
		}
	}
}
