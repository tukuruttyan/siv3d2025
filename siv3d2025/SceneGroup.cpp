#include "stdafx.h"
#include "SceneGroup.h"
#include "TitleScene.h"
#include "StageA.h"

namespace GameCore
{
	SceneGroup::SceneGroup(std::function<void(const std::type_index&)> onChangeScene)
	{
		AddScene(std::make_shared<TitleScene>(SceneBaseContext(onChangeScene)));
		AddScene(std::make_shared<StageA	>(SceneBaseContext(onChangeScene)));
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
