#include "stdafx.h"
#include "TitleScene.h"

GameCore::TitleScene::TitleScene(SceneBaseContext context)
	: SceneBase{ context }
	, m_texture{ U"example/windmill.png" }
	, m_emoji{ U"🦖"_emoji }
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
	m_texture.draw(20, 20);

	m_font(U"Hello, Siv3D!🎮").draw(64, Vec2{ 20, 340 }, ColorF{ 0.2, 0.4, 0.8 });

	m_font(U"Siv3D (シブスリーディー) は、ゲームやアプリを楽しく簡単な C++ コードで開発できるフレームワークです。")
		.draw(18, Rect{ 20, 430, 480, 200 }, Palette::Black);

	Rect{ 540, 20, 80, 80 }.draw();
	RoundRect{ 680, 20, 80, 200, 20 }.draw(ColorF{ 0.0, 0.4, 0.6 });
	Circle{ 580, 180, 40 }.draw(Palette::Seagreen);
	Line{ 540, 330, 760, 260 }.drawArrow(8, SizeF{ 20, 20 }, ColorF{ 0.4 });
	Circle{ Cursor::Pos(), 40 }.draw(ColorF{ 1.0, 0.0, 0.0, 0.5 });

	if (SimpleGUI::Button(U"count: {}"_fmt(m_count), Vec2{ 520, 370 }, 120, (m_checked == false)))
	{
		++m_count;
	}

	SimpleGUI::CheckBox(m_checked, U"Lock \U000F033E", Vec2{ 660, 370 }, 120);
	SimpleGUI::Slider(U"speed: {:.1f}"_fmt(m_speed), m_speed, 100, 400, Vec2{ 520, 420 }, 140, 120);

	if (KeyLeft.pressed())
	{
		m_playerPosX = Max((m_playerPosX - m_speed * Scene::DeltaTime()), 60.0);
		m_isPlayerFacingRight = false;
	}

	if (KeyRight.pressed())
	{
		m_playerPosX = Min((m_playerPosX + m_speed * Scene::DeltaTime()), 740.0);
		m_isPlayerFacingRight = true;
	}

	m_emoji.scaled(0.75).mirrored(m_isPlayerFacingRight).drawAt(m_playerPosX, 540);
}

void GameCore::TitleScene::OnExit()
{
}
