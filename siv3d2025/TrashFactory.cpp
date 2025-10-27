#include "stdafx.h"
#include "TrashFactory.h"
#include "SpawnCooldown.h"

GameCore::TrashFactory::TrashFactory(std::vector<std::pair<SpawnCooldown, const CreatureBasicParam>> spawnEnemies, Vec2 position)
	: m_summonCreatureParam(spawnEnemies),
	m_position(position)
{
}

void GameCore::TrashFactory::Update(std::function<void(TrashEnemy)> addSceneTrashEnemy)
{
	for (auto& [cooldown, summonEnemyBasicParam] : m_summonCreatureParam)
	{
		cooldown = cooldown.WithTick(s3d::Scene::DeltaTime());

		bool didCount = false;
		cooldown = cooldown.WithCheckCount(didCount);

		if (didCount)
		{
			addSceneTrashEnemy(TrashEnemy(summonEnemyBasicParam, m_position));
		}
	}
}

void GameCore::TrashFactory::Draw()
{
	m_texture.draw(m_position);
}
