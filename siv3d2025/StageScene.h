#pragma once
#include "SceneBase.h"
#include "SeaDeepest.h"
#include "StageSceneContext.h"
#include "DeepSeaFish.h"
#include "TrashEnemy.h"
#include <optional>

#include "KirimiButton.h"
#include "StageUI.h"

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
		void UpdateScroll();


		std::optional<StageSceneContext> m_context;
		s3d::Camera2D m_camera;

		SeaDeepest seaDeepest;
		std::vector<DeepSeaFish> m_deepSeaFishes;
		std::vector<TrashEnemy > m_trashEnemies;
		StageUI m_stageUI = StageUI { };

		Vec2 m_playerPos = {0, 0};
		double m_resource = 0;
		bool m_canvasOpen = false;
	};
}
