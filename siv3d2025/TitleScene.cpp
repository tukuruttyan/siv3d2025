#include "stdafx.h"
#include "TitleScene.h"
#include "StageA.h"

GameCore::TitleScene::TitleScene(SceneBaseContext context)
	: SceneBase{ context }
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
	if (SimpleGUI::Button(U"GameStart", Vec2{ 520, 370 }, 120, (m_checked == false)))
	{
		OnChangeScene<StageA>();
	}
}

void GameCore::TitleScene::OnExit()
{
}
