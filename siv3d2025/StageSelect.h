#pragma once
#include "SceneBase.h"
#include "StageSelectPlayer.h"
#include "StageSceneContext.h"
#include "TrashEnemyParams.h"
#include "OnSpawnTrashEnemy.h"
#include <Siv3D.hpp>

namespace GameCore
{
	class StageSelect final : public SceneBase
	{
	public:
		explicit StageSelect(SceneBaseContext context, std::function<void(StageSceneContext)> onChangeStageScene);

	private:
		void OnEnter() override;
		void Update () override;
		void OnExit () override;

		std::function<void(StageSceneContext)> m_onChangeStageScene;
		const s3d::Texture m_backGround{ U"example/windmill.png" };
		StageSelectPlayer m_player;

		std::vector<std::pair<s3d::Vec2, StageSceneContext>> m_positionScenePairs{
			{ {100, 300}, {std::make_shared<TrashFactory>(std::vector<OnSpawnTrashEnemy>{OnSpawnTrashEnemy{SpawnCooldown{0.2f}, EnemyParams::TRASH_AKIKAN(), EnemyParams::TRASH_AKIKAN_ANIM()}}, 40), -2000.0f}},
			{ {100, 300}, {std::make_shared<TrashFactory>(std::vector<OnSpawnTrashEnemy>{OnSpawnTrashEnemy{SpawnCooldown{2.0f}, EnemyParams::TRASH_AKIKAN(), EnemyParams::TRASH_AKIKAN_ANIM()}}, 40), -2000.0f}},
			{ {100, 300}, {std::make_shared<TrashFactory>(std::vector<OnSpawnTrashEnemy>{OnSpawnTrashEnemy{SpawnCooldown{2.0f}, EnemyParams::TRASH_AKIKAN(), EnemyParams::TRASH_AKIKAN_ANIM()}}, 40), -2000.0f}},
			{ {100, 300}, {std::make_shared<TrashFactory>(std::vector<OnSpawnTrashEnemy>{OnSpawnTrashEnemy{SpawnCooldown{2.0f}, EnemyParams::TRASH_AKIKAN(), EnemyParams::TRASH_AKIKAN_ANIM()}}, 40), -2000.0f}}
		};

		size_t m_currentIndex = 0;

		s3d::Camera2D m_camera;
		s3d::Vec2 m_cameraCenter;
	};
}
