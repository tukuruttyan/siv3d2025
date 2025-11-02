#include "stdafx.h"
#include "SeaDeepest.h"
#include "SpriteAnimation.h"

GameCore::SeaDeepest::SeaDeepest(const Vec2 position, std::function<void()> onGameOver)
	: m_position(position),
	  m_onGameOver(onGameOver)
{
}

void GameCore::SeaDeepest::Update(const std::function<void(DeepSeaFish)>& addSceneDeepSeaFish, const std::function<void(DeepSeaFish&)>& removeSceneDeepSeaFish)
{
	if (KeySpace.down())
	{
		const auto spawnFishPosition = Vec2{ Scene::Center().x + Scene::Width() * Random(-0.2, 0.2), m_position.y };

	}
}

void GameCore::SeaDeepest::Draw() const
{
	m_texture.fitted(Scene::Size()).draw(m_position + Vec2{0, -420});
}

void GameCore::SeaDeepest::TakeOnAttack(int takeAttackPower)
{
	m_health -= takeAttackPower;

	if (m_health <= 0)
	{
		m_onGameOver();
	}
}
