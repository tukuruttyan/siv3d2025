#pragma once
#include "SpawnCooldown.h"
#include "CreatureBasicParam.h"
#include "TrashEnemyAnimation.h"
#include "TrashEnemy.h"

namespace GameCore
{
	class OnSpawnTrashEnemy final
	{
	public:
		explicit OnSpawnTrashEnemy(SpawnCooldown spawnCooldown, CreatureBasicParam param, TrashEnemyAnimation animation);
		void Tick(const Vec2& spawnPosition, std::function<void(TrashEnemy)> addSceneTrashEnemy, const std::function<void(TrashEnemy&)>& removeSceneTrashEnemy);


	private:
		SpawnCooldown m_spawnCooldown;
		const CreatureBasicParam m_basicParam;
		TrashEnemyAnimation	m_animation;
	};
}
