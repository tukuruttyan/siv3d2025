#include "stdafx.h"
#include "TrashFactory.h"
#include "SpawnCooldown.h"

GameCore::TrashFactory::TrashFactory(std::vector<OnSpawnTrashEnemy> spawnEnemies, int health)
	: onSummonCreatures(spawnEnemies),
	  m_health(health),
	  m_position(Scene::Width()/2, 0)
{
}

void GameCore::TrashFactory::Init(std::function<void()> onGameClear)
{
	m_onGameClear = onGameClear;
}

void GameCore::TrashFactory::Update(std::function<void(TrashEnemy)> addSceneTrashEnemy, const std::function<void(TrashEnemy&)>& removeSceneTrashEnemy)
{
	for (auto& onSummonCreature : onSummonCreatures)
	{
		onSummonCreature.Tick(Vec2{ Scene::Center().x + Scene::Width() * Random(-0.2, 0.2), m_position.y + 550}, addSceneTrashEnemy, removeSceneTrashEnemy);
	}
}

void GameCore::TrashFactory::Draw()
{
	m_texture.resized(1100).draw(m_position + Vec2{ -530, -530 });
}

void GameCore::TrashFactory::TakeOnAttack(int attackPower)
{
	m_health -= attackPower;
	if (m_health <= 0)
	{
		Print << U"stage clear";
		m_onGameClear();
	}
}
