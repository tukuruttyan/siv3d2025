#include "stdafx.h"
#include "SceneBaseContext.h"

GameCore::SceneBaseContext::SceneBaseContext(std::function<void(const std::type_index&)> onChangeScene)
	: m_onChangeScene(std::move(onChangeScene))
{
}

void GameCore::SceneBaseContext::OnChangeScene(const std::type_index& sceneType) const
{
	m_onChangeScene(sceneType);
}
