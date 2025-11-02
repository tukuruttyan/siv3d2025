#include "stdafx.h"
#include "StageSceneContext.h"

namespace GameCore
{
	StageSceneContext::StageSceneContext(std::shared_ptr<const TrashFactory> trashFactory, float sceneHeight)
		: m_trashFactory(std::move(trashFactory))
		, m_sceneHeight(sceneHeight)
	{

	}

	void StageSceneContext::Update()
	{
		m_resource += Scene::DeltaTime() * m_resourcesPerSecond;
	}

	void StageSceneContext::GameOver()
	{
		m_gameState = GameCore::GameOver;
	}

	void StageSceneContext::GameClear()
	{
		m_gameState = GameCore::GameClear;
	}

	TrashFactory& StageSceneContext::getTrashFactory() const
	{
		return const_cast<TrashFactory&>(*m_trashFactory);
	}

	float StageSceneContext::getSceneHeight() const
	{
		return m_sceneHeight;
	}

	double StageSceneContext::getScrollSpeed() const
	{
		return m_scrollSpeed;
	}

	const std::array<std::pair<const SpriteAnimation, const CreatureBasicParam>, 8>& StageSceneContext::getKirimiInventory() const
	{
		return m_kirimiInventory;
	}

	StageSceneContext& StageSceneContext::operator=(const StageSceneContext& other)
	{
		new (this) StageSceneContext(other.m_trashFactory, other.m_sceneHeight);
		return *this;
	}
}
