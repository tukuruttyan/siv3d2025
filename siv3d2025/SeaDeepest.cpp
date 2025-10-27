#include "stdafx.h"
#include "SeaDeepest.h"

void GameCore::SeaDeepest::Update(const std::function<void(DeepSeaFish)>& addSceneDeepSeaFish, const std::function<void(DeepSeaFish&)>& removeSceneDeepSeaFish)
{
	if (KeySpace.down())
	{
		addSceneDeepSeaFish(DeepSeaFish{ CreatureBasicParam{0.5f, 200.0f, 0.2f, 0.2f, 2, 1, 3, 0, 30.0f, 0, { 100, 100}, SpriteAnimation{U"example/windmill.png", 1, 1, 10.0f}, SpriteAnimation{U"example/windmill.png", 1, 1, 10.0f}}, m_position, removeSceneDeepSeaFish });
	}
}

void GameCore::SeaDeepest::Draw() const
{
	m_texture.resized(300, 300).draw(m_position);
}
