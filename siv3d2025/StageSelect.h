#pragma once
#include "SceneBase.h"
#include "StageSelectPlayer.h"
#include "StageSceneContext.h"
#include "TrashEnemyParams.h"
#include <Siv3D.hpp>

namespace GameCore
{
	class StageSelect final : public SceneBase
	{
	public:
		explicit StageSelect(SceneBaseContext context, std::function<void(StageSceneContext)> onChangeStageScene);

	private:
		void OnEnter() override;
		void Update()  override;
		void OnExit()  override;

		std::function<void(StageSceneContext)> m_onChangeStageScene;
		const s3d::Texture m_backGround{ U"example/windmill.png" };
		StageSelectPlayer m_player;

		std::vector<std::pair<s3d::Vec2, StageSceneContext>> m_positionScenePairs{
			{ {100, 300}, {std::make_shared<TrashFactory>(std::vector<std::pair<SpawnCooldown, const CreatureBasicParam>>{std::make_pair(SpawnCooldown(10.0f), EnemyParams::TRASH_BAG())}, s3d::Vec2{0, -800 }), -800.0f  } },
			{ {300, 300}, {std::make_shared<TrashFactory>(std::vector<std::pair<SpawnCooldown, const CreatureBasicParam>>{std::make_pair(SpawnCooldown(10.0f), EnemyParams::TRASH_BAG())}, s3d::Vec2{0, -600 }), -600.0f  } },
			{ {500, 300}, {std::make_shared<TrashFactory>(std::vector<std::pair<SpawnCooldown, const CreatureBasicParam>>{std::make_pair(SpawnCooldown(10.0f), EnemyParams::TRASH_BAG())}, s3d::Vec2{0, -900 }), -900.0f  } },
			{ {700, 300}, {std::make_shared<TrashFactory>(std::vector<std::pair<SpawnCooldown, const CreatureBasicParam>>{std::make_pair(SpawnCooldown(10.0f), EnemyParams::TRASH_BAG())}, s3d::Vec2{0, -1000}), -1000.0f } }
		};

		size_t m_currentIndex = 0;

		s3d::Camera2D m_camera;
		s3d::Vec2 m_cameraCenter;
	};
}
