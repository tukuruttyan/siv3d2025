#include "StageSelect.h"
#include "StageScene.h"
#include "TitleScene.h"

namespace GameCore
{
	StageSelect::StageSelect(SceneBaseContext context, std::function<void(StageSceneContext)> onChangeStageScene)
		: SceneBase(context)
		, m_onChangeStageScene(onChangeStageScene)
	{
	}

	void StageSelect::OnEnter()
	{
		m_currentIndex = 0;
		m_cameraCenter = m_positionScenePairs[m_currentIndex].first;
		m_camera.jumpTo(m_cameraCenter, 1.0);
	}

	void StageSelect::Update()
	{
		if (s3d::KeyRight.down() && m_currentIndex + 1 < m_positionScenePairs.size())
		{
			m_currentIndex++;
		}
		else if (s3d::KeyLeft.down() && m_currentIndex > 0)
		{
			m_currentIndex--;
		}

		const auto& [target, context] = m_positionScenePairs[m_currentIndex];
		m_cameraCenter = s3d::Math::Lerp(m_cameraCenter, target, 0.1);
		m_camera.setTargetCenter(m_cameraCenter);
		m_camera.update();

		const s3d::Transformer2D transformer{ m_camera.createTransformer() };

		m_backGround.resized(Scene::Size()).draw();
		m_player.update(target);
		m_player.draw();

		if (s3d::KeySpace.down())
		{
			m_onChangeStageScene(context);
		}
	}

	void StageSelect::OnExit()
	{
	}
}
