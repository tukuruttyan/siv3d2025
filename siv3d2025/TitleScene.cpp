#include "stdafx.h"
#include "TitleScene.h"
#include "StageSelect.h"
#include "TrashEnemyParams.h"

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
	Scene::SetBackground(Palette::Black);
}

void GameCore::TitleScene::Update()
{
	ScopedRenderStates2D blend{ BlendState::Additive};
	texture.resized(1950).drawAt(Scene::Center());
	{
		renderTexture.clear(ColorF{ 0.3 });
		Circle{ Scene::Width() * 0.3, Scene::Height(), Scene::Height() * 1}.drawPie(10_deg, 40_deg, ColorF{ 0.3 }, ColorF{ 0 });
		Circle{ Scene::Width() * 0.7, Scene::Height(), Scene::Height() * 1 }.drawPie(-10_deg, -40_deg, ColorF{ 0.3 }, ColorF{0});
		Circle{ Scene::Width() * 0.05, Scene::Height(), Scene::Height() * 1 }.drawPie(20_deg, 50_deg, ColorF{ 0.3 }, ColorF{ 0 });
		Circle{ Scene::Width() * 0.95, Scene::Height(), Scene::Height() * 1 }.drawPie(-20_deg, -50_deg, ColorF{ 0.3 }, ColorF{ 0 });
	}

	Graphics2D::Flush();
	renderTexture.resolve();
	renderTexture.draw();

	ScopedRenderStates2D ui{ BlendState::Default2D };
	if (SimpleGUI::Button(U"GameStart", Scene::Center() - Vec2{ 300, -450 }, 600, (m_checked == false)))
	{
		m_onChangeStageScene({ std::make_shared<TrashFactory>(std::vector<OnSpawnTrashEnemy>{
   OnSpawnTrashEnemy{SpawnCooldown{0.2f}, EnemyParams::TrashEnemyParams()[static_cast<std::size_t>(EnemyParams::TrashEnemyType::Akikan)], EnemyParams::TrashEnemyAnims()[static_cast<std::size_t>(EnemyParams::TrashEnemyType::Akikan)]},
			OnSpawnTrashEnemy{SpawnCooldown{1.0f}, EnemyParams::TrashEnemyParams()[static_cast<std::size_t>(EnemyParams::TrashEnemyType::Taiya)], EnemyParams::TrashEnemyAnims()[static_cast<std::size_t>(EnemyParams::TrashEnemyType::Taiya)]},
			OnSpawnTrashEnemy{SpawnCooldown{10.0f}, EnemyParams::TrashEnemyParams()[static_cast<std::size_t>(EnemyParams::TrashEnemyType::Bag)], EnemyParams::TrashEnemyAnims()[static_cast<std::size_t>(EnemyParams::TrashEnemyType::Bag)]}
		}, 40), -2000.0f });
	}
}

void GameCore::TitleScene::OnExit()
{
}
