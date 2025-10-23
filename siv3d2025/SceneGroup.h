#pragma once
#include <unordered_map>
#include <typeindex>
#include <memory>
#include "SceneBase.h"

namespace GameCore
{
	class SceneGroup final
	{
	public:
		SceneGroup(std::function<void(const std::type_index&)> onChangeScene);

		std::shared_ptr<SceneBase> Catch(const std::type_index& typeIndex);

	private:
		template<typename T>
		void AddScene(const std::shared_ptr<T>& scene);

		std::unordered_map<std::type_index, std::shared_ptr<SceneBase>> m_scenes;
	};

	template<typename T>
	inline void SceneGroup::AddScene(const std::shared_ptr<T>& scene)
	{
		static_assert(std::is_base_of_v<SceneBase, T>, "T must derive from SceneBase");
		const std::type_index typeIndex = typeid(T);
		m_scenes[typeIndex] = scene;
	}
}
