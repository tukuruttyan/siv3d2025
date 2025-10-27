#pragma once
#include "SceneBase.h"
#include "SeaDeepest.h"
#include "StageSceneContext.h"
#include "DeepSeaFish.h"
#include "TrashEnemy.h"
#include <optional>

namespace GameCore
{
	class StageScene : public SceneBase
	{
	public:
		explicit StageScene(SceneBaseContext context);
		void Init(StageSceneContext sceneContext);

	private:
		void OnEnter() override;
		void Update () override;
		void OnExit () override;

		std::optional<StageSceneContext> m_context;
		s3d::Camera2D m_camera;

		SeaDeepest seaDeepest;
		std::vector<DeepSeaFish> m_deepSeaFishes;
		std::vector<TrashEnemy > m_trashEnemies;

		Vec2 m_playerPos;
	};
}
