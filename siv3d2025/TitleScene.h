#pragma once
#include "SceneBase.h"
#include "SceneBaseContext.h"

namespace GameCore
{
	class TitleScene final : public SceneBase
	{
	public:
		TitleScene(SceneBaseContext context);

	private:
		void OnEnter() override;
		void Update () override;
		void OnExit () override;

		s3d::Font    m_font;
		int32        m_count = 0;
		bool         m_checked = false;
		double       m_speed = 200.0;
		double       m_playerPosX = 400.0;
		bool         m_isPlayerFacingRight = true;
	};
}
