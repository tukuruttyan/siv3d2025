#include "stdafx.h"
#include "TrashFactory.h"
#include "SpawnCooldown.h"

GameCore::TrashFactory::TrashFactory(std::vector<std::pair<SpawnCooldown, TrashEnemy>> spawnEnemies, Vec2 position)
	: m_spawnEnemies(spawnEnemies),
	m_position(position)
{
}

void GameCore::TrashFactory::Tick()
{
	for (auto& [cooldown, enemy] : m_spawnEnemies)
	{
		cooldown = cooldown.WithTick(s3d::Scene::DeltaTime());

		bool didCount = false;
		cooldown = cooldown.WithCheckCount(didCount);

		if (didCount)
		{

		}
	}
}

void GameCore::TrashFactory::Draw()
{

}
