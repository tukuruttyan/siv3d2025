#include "stdafx.h"
#include "TrashFactory.h"
#include "SpawnCooldown.h"

GameCore::TrashFactory::TrashFactory(std::vector<OnSpawnTrashEnemy> spawnEnemies, int health)
	: onSummonCreatures(spawnEnemies),
	  m_health(health),
	  m_position(Scene::Width() / 2, 0)
{
}

void GameCore::TrashFactory::Update(std::function<void(TrashEnemy)> addSceneTrashEnemy, const std::function<void(TrashEnemy&)>& removeSceneTrashEnemy)
{
	for (auto& onSummonCreature : onSummonCreatures)
	{
		onSummonCreature.Tick(Vec2{ static_cast<float>(Random(0, Scene::Width() - 90)), m_position.y }, addSceneTrashEnemy, removeSceneTrashEnemy);
	}
}

void GameCore::TrashFactory::Draw()
{
	m_texture.draw(m_position);
}

void GameCore::TrashFactory::TakeOnAttack(int attackPower)
{

}
