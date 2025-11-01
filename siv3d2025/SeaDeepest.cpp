#include "stdafx.h"
#include "SeaDeepest.h"

GameCore::SeaDeepest::SeaDeepest(const Vec2 position)
	: m_position(position)
{
}

void GameCore::SeaDeepest::Update(const std::function<void(DeepSeaFish)>& addSceneDeepSeaFish, const std::function<void(DeepSeaFish&)>& removeSceneDeepSeaFish)
{
	if (KeySpace.down())
	{
		const auto spawnFishPosition = Vec2{ static_cast<float>(s3d::Random(0, Scene::Width() - 90)), m_position.y };
		addSceneDeepSeaFish(DeepSeaFish{ CreatureBasicParam{0.5f, -200.0f, 0.2f, 0.2f, 2, 1, 3, 0, 30.0f, 0, {100, 100}, {100, 100}, SpriteAnimation{U"example/windmill.png", 1, 1, 10.0f}, SpriteAnimation{U"example/windmill.png", 1, 1, 10.0f}}, spawnFishPosition, removeSceneDeepSeaFish });
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
