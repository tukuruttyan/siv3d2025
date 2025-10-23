#include "stdafx.h"
#include "SceneBaseContext.h"

GameCore::SceneBaseContext::SceneBaseContext(std::function<void(const std::type_index&)> m_onChangeScene)
	: m_onChangeScene(std::move(m_onChangeScene))
{
}

void GameCore::SceneBaseContext::OnChangeScene(const std::type_index& sceneType) const
{
	m_onChangeScene(sceneType);
}
