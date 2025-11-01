#include "stdafx.h"
#include "SeaDeepest.h"
#include "SpriteAnimation.h"

GameCore::SeaDeepest::SeaDeepest(const Vec2 position)
	: m_position(position)
{
}

void GameCore::SeaDeepest::Update(const std::function<void(DeepSeaFish)>& addSceneDeepSeaFish, const std::function<void(DeepSeaFish&)>& removeSceneDeepSeaFish)
{
	if (KeySpace.down())
	{
		const auto spawnFishPosition = Vec2{ static_cast<float>(s3d::Random(0, Scene::Width() - 90)), m_position.y };
	}
}

void GameCore::SeaDeepest::Draw() const
{
	m_texture.resized(300, 300).draw(m_position);
}

void GameCore::SeaDeepest::TakeOnAttack(int takeAttackPower)
{
	m_health -= takeAttackPower;
}
