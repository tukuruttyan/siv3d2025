#include "stdafx.h"
#include "StageSceneContext.h"

namespace GameCore
{
	StageSceneContext::StageSceneContext(std::shared_ptr<const TrashFactory> trashFactory, float sceneHeight)
		: m_trashFactory(std::move(trashFactory))
		, m_sceneHeight(sceneHeight)
	{
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

	StageSceneContext& StageSceneContext::operator=(const StageSceneContext& other)
	{
		new (this) StageSceneContext(other.m_trashFactory, other.m_sceneHeight);
		return *this;
	}
}
