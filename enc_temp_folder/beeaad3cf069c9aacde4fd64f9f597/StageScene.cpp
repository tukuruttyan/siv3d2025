#include "stdafx.h"
#include "StageScene.h"
#include <ranges>

#include "KirimiButton.h"

namespace GameCore
{
	StageScene::StageScene(SceneBaseContext context)
		: SceneBase(context)
	{
	}

	void StageScene::Init(StageSceneContext sceneContext)
	{
		m_context = sceneContext;
		auto costs = m_context->getCosts();

		m_kirimiButtons.clear();


		const std::array<String, 8> buttonIcons{ U"い", U"ろ", U"は", U"に", U"ほ", U"へ", U"と", U"ち" };

		for (int i = 0; i < costs.size(); i++)
		{
			const Point pos{ 100, i * 100 };
			m_kirimiButtons.push_back(KirimiButton{ pos, costs[i], buttonIcons[i]});
		}
	}

	void StageScene::OnEnter()
	{
		Scene::SetBackground( Palette::Gray);
		m_playerPos = Scene::Center();
		m_camera = Camera2D(m_playerPos, 1, CameraControl::None_);

	}

	void StageScene::Update()
	{
		m_camera.update();
		{
			const auto t1 = m_camera.createTransformer();

			UpdateScroll();

			Rect{
				Point{
					0,
					Scene::Height() / 2
				},
				Size{
					Scene::Width(),
					-static_cast<int>(m_context->getSceneHeight())
				}
			}.draw(
				Arg::top = Palette::Lightseagreen,
				Arg::bottom = Palette::Darkseagreen
			);

			m_context .value().getTrashFactory().Update([this](TrashEnemy enemy) { m_trashEnemies.push_back(enemy); });
			m_context .value().getTrashFactory().Draw();
			seaDeepest.Update([this](DeepSeaFish fish) { m_deepSeaFishes.push_back(fish); });
			seaDeepest.Draw();
			for (auto& fish : m_deepSeaFishes)
			{
				const auto deepSeaFishAttackables = m_trashEnemies
					| std::views::transform([](TrashEnemy& fish) -> ITakableSeaFishAttack* { return &fish; })
					| std::ranges::to<std::vector<ITakableSeaFishAttack*>>();

				fish.Update(deepSeaFishAttackables);
				fish.Draw  ();
			}
			for (auto& trashEnemy : m_trashEnemies)
			{
				const auto trashEnemyAttackables = m_deepSeaFishes
					| std::views::transform([](DeepSeaFish& fish) -> ITakableTrashEnemyAttack* { return &fish; })
					| std::ranges::to<std::vector<ITakableTrashEnemyAttack*>>();

				trashEnemy.Update(trashEnemyAttackables);
				trashEnemy.Draw();
			}
		}
		Circle{ 690, 110, 100 }.draw(ColorF{ 0.8 });



		for (const auto& button : m_kirimiButtons)
		{
			button.draw(600);
		}

	}

	void StageScene::OnExit()
	{
	}

	void StageScene::UpdateScroll()
	{
		const double dt = Scene::DeltaTime();
		const double speed = m_context->getScrollSpeed();

		// 連続移動（キー）は時間でスケール
		double dy_continuous = (KeyDown.pressed() - KeyUp.pressed()) * speed * dt;

		// ホイールはイベント量。dtは掛けない
		double dy_wheel = Mouse::Wheel() * (speed * 0.15);

		m_playerPos += Vec2(0.0, dy_continuous + dy_wheel);

		// 範囲制限
		m_playerPos.y = Math::Clamp(m_playerPos.y, Scene::Height()*0.05, static_cast<int>(-m_context->getSceneHeight()));

		m_camera.setTargetCenter(m_playerPos);
	}

	void StageScene::DrawMiniMap(Float2 pos)
	{
		Transformer2D t(Mat3x2::Translate(pos));

//		Rect{ 7, 10, 130, 330 }.draw(ColorF{ 0, 0, 0, 0.3 });
		Rect{ 7, 320, 120, 20 }.rounded(0, 0, 0, 20).draw(ColorF{0, 0, 0, 0.3});
		Rect{ 127, 10, 20, 330 }.rounded(0, 20, 20, 0).draw(ColorF{ 0, 0, 0, 0.3 });

		Rect{ 10, 10, 110, 310 }.draw(ColorF{ 1, 1, 1, 0.8 });


		RoundRect{ 15, 15, 100, 300, 10 }.drawFrame(0, 15, ColorF{ 0.3 });

		RoundRect{ 0, 0, 130, 330, 20 }.drawFrame(5, 0, ColorF{ 0 });

		Rect{ Point{ 15, 47 }, Size{ 100, 3 } }.draw(Palette::Crimson);
		Rect{ Point{ 15, 297 }, Size{ 100, 3 } }.draw(Palette::Chartreuse);

		Rect{ Point{ 25, 50 }, Size{ 80, 50 } }.drawFrame(1, Palette::Dodgerblue);

		// 内側の影表現
		Circle{ 105, 25, 10 }.drawPie(0_deg, 90_deg, ColorF{ 1, 1, 1, 0 }, ColorF{ 1 });
		Circle{ 105, 305, 10 }.drawPie(90_deg, 90_deg, ColorF{ 1, 1, 1, 0 }, ColorF{ 1 });
		Circle{ 25, 305, 10 }.drawPie(180_deg, 90_deg, ColorF{ 1, 1, 1, 0 }, ColorF{ 1 });
		Circle{ 25, 25, 10 }.drawPie(270_deg, 90_deg, ColorF{ 1, 1, 1, 0 }, ColorF{ 1 });

		Rect{ Point{ 15, 25 }, Size{ 10, 280 } }.draw(Arg::left(1), Arg::right(1, 1, 1, 0));
		Rect{ Point{ 105, 25 }, Size{ 10, 280 } }.draw(Arg::left(1, 1, 1, 0), Arg::right(1));
		Rect{ Point{ 25, 15 }, Size{ 80, 10 } }.draw(Arg::top(1), Arg::bottom(1, 1, 1, 0));
		Rect{ Point{ 25, 305 }, Size{ 80, 10 } }.draw(Arg::top(1, 1, 1, 0), Arg::bottom(1));
	}
}
