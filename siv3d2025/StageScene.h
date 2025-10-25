#pragma once
#include "SceneBase.h"
#include "StageSceneContext.h"
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
		void Update()  override;
		void OnExit()  override;

		const s3d::Texture m_backGround{ U"example/windmill.png" };
		std::optional<StageSceneContext> m_context;
		s3d::Camera2D m_camera;
	};
}
