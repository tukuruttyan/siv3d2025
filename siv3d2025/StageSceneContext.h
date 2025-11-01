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
		double getStartResources() const;
		double getResourcesPerSecond() const;
		const std::array<CreatureBasicParam, 8>& getKirimiInventory() const;
		StageSceneContext& operator=(const StageSceneContext& other);
	private:
		std::shared_ptr<const TrashFactory> m_trashFactory;
		const float m_sceneHeight;
		const double m_scrollSpeed = 300.0;
		std::array<CreatureBasicParam, 8> m_kirimiInventory{
			CreatureBasicParam{0.5f, 1.5f, 0.2f, 0.2f, 2, 1, 3, 0, 10.0f, 0, Vec2{100, 100}},
			CreatureBasicParam{0.5f, 1.5f, 0.2f, 0.2f, 2, 1, 3, 0, 10.0f, 0, Vec2{100, 100}},
			CreatureBasicParam{0.5f, 1.5f, 0.2f, 0.2f, 2, 1, 3, 0, 10.0f, 0, Vec2{100, 100}},
			CreatureBasicParam{0.5f, 1.5f, 0.2f, 0.2f, 2, 1, 3, 0, 10.0f, 0, Vec2{100, 100}},
			CreatureBasicParam{0.5f, 1.5f, 0.2f, 0.2f, 2, 1, 3, 0, 10.0f, 0, Vec2{100, 100}},
			CreatureBasicParam{0.5f, 1.5f, 0.2f, 0.2f, 2, 1, 3, 0, 10.0f, 0, Vec2{100, 100}},
			CreatureBasicParam{0.5f, 1.5f, 0.2f, 0.2f, 2, 1, 3, 0, 10.0f, 0, Vec2{100, 100}},
			CreatureBasicParam{0.5f, 1.5f, 0.2f, 0.2f, 2, 1, 3, 0, 10.0f, 0, Vec2{100, 100}},
		};

		const double m_startResources = 1000;
		const double m_resourcesPerSecond = 5;
	};
}
