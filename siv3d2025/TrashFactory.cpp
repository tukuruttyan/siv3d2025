#include "stdafx.h"
#include "TrashFactory.h"
#include "SpawnCooldown.h"

GameCore::TrashFactory::TrashFactory(std::vector<std::pair<SpawnCooldown, const CreatureBasicParam>> spawnEnemies, int health)
	: m_summonCreatureParam(spawnEnemies),
	  m_health(health),
	  m_position(Scene::Width() / 2, 0)
{
}

void GameCore::TrashFactory::Update(std::function<void(TrashEnemy)> addSceneTrashEnemy, const std::function<void(TrashEnemy&)>& removeSceneTrashEnemy)
{
	for (auto& [cooldown, summonEnemyBasicParam] : m_summonCreatureParam)
	{
		cooldown = cooldown.WithTick(s3d::Scene::DeltaTime());

		bool didCount = false;
		cooldown = cooldown.WithCheckCount(didCount);

		if (didCount)
		{
			addSceneTrashEnemy(TrashEnemy(summonEnemyBasicParam, Vec2{ static_cast<float>(Random(0, Scene::Width() - 90)), m_position.y}, removeSceneTrashEnemy));
		}
	}
}

void GameCore::TrashFactory::Draw()
{
	m_texture.draw(m_position);
}

void GameCore::TrashFactory::TakeOnAttack(int attackPower)
{

}
