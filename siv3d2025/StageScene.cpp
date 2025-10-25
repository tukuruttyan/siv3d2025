#include "stdafx.h"
#include "StageScene.h"

namespace GameCore
{
	StageScene::StageScene(SceneBaseContext context)
		: SceneBase(context)
	{
	}

	void StageScene::Init(StageSceneContext sceneContext)
	{
		m_context = sceneContext;
	}

	void StageScene::OnEnter()
	{
	}

	void StageScene::Update()
	{
		const s3d::Transformer2D transformer{ m_camera.createTransformer() };

		m_backGround.resized(Scene::Size()).draw();

		double scrollDelta = 0.0;
		if (s3d::KeyUp.pressed())
		{
			scrollDelta -= m_context->getScrollSpeed() * s3d::Scene::DeltaTime();
		}
		if (s3d::KeyDown.pressed())
		{
			scrollDelta += m_context->getScrollSpeed() * s3d::Scene::DeltaTime();
		}

		s3d::Vec2 cameraCenter = m_camera.getCenter() + s3d::Vec2{ 0.0, scrollDelta };
		m_camera.jumpTo(cameraCenter, m_camera.getScale());
		m_camera.update();

		m_context->getTrashFactory().Tick();
	}

	void StageScene::OnExit()
	{
	}
}
