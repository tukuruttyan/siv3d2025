#pragma once
#include <functional>
#include <typeindex>

namespace GameCore
{
	struct SceneBaseContext final
	{
	public:
		explicit SceneBaseContext(std::function<void(const std::type_index&)> onChangeScene);

		[[nodiscard]] void OnChangeScene(const std::type_index& sceneType) const;

	private:
		std::function<void(const std::type_index&)> m_onChangeScene;
	};
}
