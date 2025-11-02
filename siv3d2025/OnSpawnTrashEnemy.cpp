#include "stdafx.h"
#include "OnSpawnTrashEnemy.h"

GameCore::OnSpawnTrashEnemy::OnSpawnTrashEnemy(SpawnCooldown spawnCooldown, CreatureBasicParam param, TrashEnemyAnimation animation)
	: m_spawnCooldown(spawnCooldown),
	  m_basicParam	 (param		   ),
	  m_animation	 (animation	   )
{
}

void GameCore::OnSpawnTrashEnemy::Tick(const Vec2& spawnPosition, std::function<void(TrashEnemy)> addSceneTrashEnemy, const std::function<void(TrashEnemy&)>& removeSceneTrashEnemy)
{
	m_spawnCooldown = m_spawnCooldown.WithTick(s3d::Scene::DeltaTime());
	bool didCount = false;
	m_spawnCooldown = m_spawnCooldown.WithCheckCount(didCount);

	if (didCount)
	{
		addSceneTrashEnemy(TrashEnemy(m_basicParam, m_animation, spawnPosition, removeSceneTrashEnemy));
	}
}
