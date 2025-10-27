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
	}

	void StageScene::Update()
	{
		const s3d::Transformer2D transformer{ m_camera.createTransformer() };
		m_backGround.resized(Scene::Size()).draw();

		double scrollDelta = 0.0;
		if (s3d::KeyUp  .pressed()) { scrollDelta -= m_context->getScrollSpeed() * s3d::Scene::DeltaTime(); }
		if (s3d::KeyDown.pressed()) { scrollDelta += m_context->getScrollSpeed() * s3d::Scene::DeltaTime(); }
		m_camera.jumpTo(m_camera.getCenter() + s3d::Vec2{ 0.0, scrollDelta }, m_camera.getScale());
		m_camera.update();



		m_context.value().getTrashFactory().Update(
			[this](const TrashEnemy& enemy) { m_trashEnemies.push_back(enemy); },
			[this](TrashEnemy& trashEnemy) {
				std::erase_if(m_trashEnemies, [&trashEnemy](const TrashEnemy& e) {
					return &e == &trashEnemy;
				});
			}
		);
		m_context .value().getTrashFactory().Draw();

		seaDeepest.Update(
			[this](const DeepSeaFish& fish) { m_deepSeaFishes.push_back(fish); },
			[this](DeepSeaFish& fish) {
				std::erase_if(m_deepSeaFishes, [&fish](const DeepSeaFish& e) {
					return &e == &fish;
				});
			}
		);
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

	void StageScene::OnExit()
	{
	}
}
