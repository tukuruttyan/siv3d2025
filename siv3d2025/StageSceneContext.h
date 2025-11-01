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
		const std::array<std::pair<const SpriteAnimation, const CreatureBasicParam>, 8>& getKirimiInventory() const;
		StageSceneContext& operator=(const StageSceneContext& other);
	private:
		std::shared_ptr<const TrashFactory> m_trashFactory;
		const float m_sceneHeight;
		const double m_scrollSpeed = 300.0;
		std::array<std::pair<const SpriteAnimation, const CreatureBasicParam>, 8> m_kirimiInventory{
			std::make_pair(SpriteAnimation{U"Eye.png", 3, 1, 1.0f}, CreatureBasicParam{0.5f, 1.5f, 0.2f, 0.2f, 2, 1, 3, 0, 10.0f, 0, Vec2{100, 100}}),
			std::make_pair(SpriteAnimation{U"Mouth.png", 3, 1, 1.0f}, CreatureBasicParam{0.5f, 1.5f, 0.2f, 0.2f, 2, 1, 3, 0, 10.0f, 0, Vec2{100, 100}}),
			std::make_pair(SpriteAnimation{U"PureEye.png", 3, 1, 1.0f}, CreatureBasicParam{0.5f, 1.5f, 0.2f, 0.2f, 2, 1, 3, 0, 10.0f, 0, Vec2{100, 100}}),
			std::make_pair(SpriteAnimation{U"Eye333.png", 3, 1, 1.0f}, CreatureBasicParam{0.5f, 1.5f, 0.2f, 0.2f, 2, 1, 3, 0, 10.0f, 0, Vec2{100, 100}}),
			std::make_pair(SpriteAnimation{U"Reduroko.png", 3, 1, 1.0f}, CreatureBasicParam{0.5f, 1.5f, 0.2f, 0.2f, 2, 1, 3, 0, 10.0f, 0, Vec2{100, 100}}),
			std::make_pair(SpriteAnimation{U"Reduroko1.png", 3, 1, 1.0f}, CreatureBasicParam{0.5f, 1.5f, 0.2f, 0.2f, 2, 1, 3, 0, 10.0f, 0, Vec2{100, 100}}),
			std::make_pair(SpriteAnimation{U"Reduroko2.png", 3, 1, 1.0f}, CreatureBasicParam{0.5f, 1.5f, 0.2f, 0.2f, 2, 1, 3, 0, 10.0f, 0, Vec2{100, 100}}),
			std::make_pair(SpriteAnimation{U"Reduroko3.png", 3, 1, 1.0f}, CreatureBasicParam{0.5f, 1.5f, 0.2f, 0.2f, 2, 1, 3, 0, 10.0f, 0, Vec2{100, 100}}),
		};

		const double m_startResources = 1000;
		const double m_resourcesPerSecond = 5;
	};
}
