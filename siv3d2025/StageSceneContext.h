#pragma once
#include <Siv3D.hpp>
#include <memory>
#include "TrashFactory.h"

namespace GameCore
{
	struct StageSceneContext final
	{
	public:
		StageSceneContext(std::shared_ptr<const TrashFactory> trashFactory, float sceneHeight);

		TrashFactory& getTrashFactory() const;
		float  getSceneHeight() const;
		double getScrollSpeed() const;
		const std::array<int, 8>& getCosts() const;
		StageSceneContext& operator=(const StageSceneContext& other);

	private:
		std::shared_ptr<const TrashFactory> m_trashFactory;
		const float m_sceneHeight;
		const double m_scrollSpeed = 300.0;
		std::array<int, 8> m_costs{ 100, 15, 70, 35, 200, 500, 100, 55 };
	};
}
