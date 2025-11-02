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
		m_stageUI.Init(&m_context.value(), [this](auto fishProps) { OnSpawn(fishProps); });
		m_seaDeepest = std::make_unique<SeaDeepest>(Vec2{ 0, -sceneContext.getSceneHeight() });
	}

	void StageScene::OnEnter()
	{
		Scene::SetBackground(Palette::Gray);
		m_playerPos = Scene::Center();
		m_camera = Camera2D(m_playerPos, 1, CameraControl::None_);
	}

	void StageScene::Update()
	{
		m_context->Update();

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

			m_context.value().getTrashFactory().Update(
			[this](const TrashEnemy& enemy) { m_trashEnemies.push_back(enemy); },
			[this](TrashEnemy& trashEnemy) {
				std::erase_if(m_trashEnemies, [&trashEnemy](const TrashEnemy& e) {
					return &e == &trashEnemy;
				});
			}
			);

			m_seaDeepest->Update(
				[this](const DeepSeaFish& fish) { m_deepSeaFishes.push_back(fish); },
				[this](DeepSeaFish& fish) {
					std::erase_if(m_deepSeaFishes, [&fish](const DeepSeaFish& e) {
						return &e == &fish;
					});
				}
			);
			m_context.value().getTrashFactory().Draw();
			m_seaDeepest->Draw();
			for (auto& fish : m_deepSeaFishes)
			{
				auto deepSeaFishAttackables = m_trashEnemies
					| std::views::transform([](TrashEnemy& fish) -> ITakableSeaFishAttack* { return &fish; })
					| std::ranges::to<std::vector<ITakableSeaFishAttack*>>();

				deepSeaFishAttackables.push_back(&m_context.value().getTrashFactory());

				fish.Update(deepSeaFishAttackables);
				fish.Draw();
			}
			for (auto& trashEnemy : m_trashEnemies)
			{
				auto trashEnemyAttackables = m_deepSeaFishes
					| std::views::transform([](DeepSeaFish& fish) -> ITakableTrashEnemyAttack* { return &fish; })
					| std::ranges::to<std::vector<ITakableTrashEnemyAttack*>>();

				trashEnemyAttackables.push_back(m_seaDeepest.get());

				trashEnemy.Update(trashEnemyAttackables);
				trashEnemy.Draw();
			}
		}

		m_stageUI.update(Scene::DeltaTime(), m_context->Resource(), m_canvasOpen);
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
		m_playerPos.y = Math::Clamp(m_playerPos.y, Scene::Height() * 0.05, static_cast<int>(-m_context->getSceneHeight()));

		m_camera.setTargetCenter(m_playerPos);
	}

	void StageScene::OnSpawn(Array<CanvasKirimi> fishProps)
	{
		Print << U"お魚さんうぇい";

		std::vector<Kirimi> kirimis;
		std::ranges::transform(fishProps, std::back_inserter(kirimis),
			[](const auto& fishProp)
			{
				return Kirimi{ fishProp.m_param, fishProp.rotate, fishProp.size, fishProp.position , fishProp.m_animation};
			});


		m_deepSeaFishes.push_back(
			DeepSeaFish(
				kirimis,
				Vec2(static_cast<float>(s3d::Random(0, Scene::Width() - 90)), -m_context->getSceneHeight()),
				[this](DeepSeaFish& fish)
				{
					std::erase_if(m_deepSeaFishes, [&fish](const DeepSeaFish& erase)
					{
						return &erase == &fish;
					});
				}
			)
		);
	}
}
