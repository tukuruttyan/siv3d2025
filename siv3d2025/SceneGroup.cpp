#include "stdafx.h"
#include "SceneGroup.h"
#include "TitleScene.h"

namespace GameCore
{
	SceneGroup::SceneGroup(const std::function<void(const std::type_index&)>& onChangeScene)
	{
		const SceneBaseContext sceneBaseContext(onChangeScene);

		AddScene(std::make_shared<TitleScene>(sceneBaseContext));
	}

	std::shared_ptr<SceneBase> SceneGroup::Catch(const std::type_index& typeIndex)
	{
		auto it = m_scenes.find(typeIndex);
		if (it != m_scenes.end())
		{
			return it->second;
		}
		return nullptr;
	}
}
