#pragma once
#include "SceneBase.h"
#include "SceneBaseContext.h"
#include "StageSceneContext.h"

namespace GameCore
{
	class TitleScene final : public SceneBase
	{
	public:
		TitleScene(SceneBaseContext context, std::function<void(StageSceneContext)> onChangeStageScene);



	private:
		void OnEnter() override;
		void Update () override;
		void OnExit () override;

		const MSRenderTexture renderTexture;
		Texture texture = Texture(Resource(U"images/logo.png"));
		s3d::Font    m_font;
		int32        m_count = 0;
		bool         m_checked = false;
		double       m_speed = 200.0;
		double       m_playerPosX = 400.0;
		bool         m_isPlayerFacingRight = true;
		std::function<void(StageSceneContext)> m_onChangeStageScene;
	};
}
