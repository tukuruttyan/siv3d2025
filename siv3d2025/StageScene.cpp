#include "stdafx.h"
#include "StageScene.h"
#include <ranges>

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
}
