#pragma once
#include "SceneBase.h"
#include "SceneGroup.h"
#include <typeindex>

namespace GameCore
{
	class Game final
	{
	public:
		Game();
		void RunAsync();

	private:
		void OnChangeScene(const std::type_index& typeIndex);

		SceneGroup m_sceneGroup;
		std::shared_ptr<SceneBase> m_currentScene = nullptr;
	};
}
