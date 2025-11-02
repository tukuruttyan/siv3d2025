#include "stdafx.h"
#include "SceneGroup.h"
#include "TitleScene.h"
#include "StageScene.h"
#include "StageSelect.h"

namespace GameCore
{
	SceneGroup::SceneGroup(std::function<void(const std::type_index&)> onChangeScene)
	{
		AddScene(std::make_shared<TitleScene >(SceneBaseContext(onChangeScene), [this, onChangeScene](const StageSceneContext context)
			{
				auto stageScene = std::dynamic_pointer_cast<StageScene>(Catch(typeid(StageScene)));
				if (stageScene)
				{
					stageScene->Init(context);
				}
				onChangeScene(typeid(StageScene));
			}));
		AddScene(std::make_shared<StageScene >(SceneBaseContext(onChangeScene)));
		AddScene(std::make_shared<StageSelect>(SceneBaseContext(onChangeScene), [this, onChangeScene](const StageSceneContext context)
			{
				auto stageScene = std::dynamic_pointer_cast<StageScene>(Catch(typeid(StageScene)));
				if (stageScene)
				{
					stageScene->Init(context);
				}
				onChangeScene(typeid(StageScene));
			}));
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
