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

		const s3d::Texture m_backGround{ U"example/windmill.png" };
		std::optional<StageSceneContext> m_context;
		s3d::Camera2D m_camera;

		SeaDeepest seaDeepest;
		std::vector<DeepSeaFish> m_deepSeaFishes;
		std::vector<TrashEnemy > m_trashEnemies;
	};
}
