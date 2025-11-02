#include "stdafx.h"
#include "TitleScene.h"
#include "StageSelect.h"

GameCore::TitleScene::TitleScene(SceneBaseContext context, std::function<void(StageSceneContext)> onChangeStageScene)
	: SceneBase{ context }
	, m_onChangeStageScene(onChangeStageScene)
	, m_font{ FontMethod::MSDF, 48, Typeface::Bold }
{
	const Font emojiFont{ 48, Typeface::ColorEmoji };
	m_font.addFallback(emojiFont);
}

void GameCore::TitleScene::OnEnter()
{
	Scene::SetBackground(ColorF{ 0.6, 0.8, 0.7 });
}

void GameCore::TitleScene::Update()
{
	texture.resized(1200, 900).draw(Vec2{430, -100});

	if (SimpleGUI::Button(U"GameStart", Vec2{ 430, 600 }, 600, (m_checked == false)))
	{
		m_onChangeStageScene({ std::make_shared<TrashFactory>(std::vector<OnSpawnTrashEnemy>{OnSpawnTrashEnemy{SpawnCooldown{0.2f}, EnemyParams::TRASH_AKIKAN(), EnemyParams::TRASH_AKIKAN_ANIM()}}, 40), -2000.0f });
	}
}

void GameCore::TitleScene::OnExit()
{
}
