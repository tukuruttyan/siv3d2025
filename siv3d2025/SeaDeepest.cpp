#include "stdafx.h"
#include "SeaDeepest.h"
#include "SpriteAnimation.h"

GameCore::SeaDeepest::SeaDeepest(const Vec2 position, std::function<void()> onGameOver)
	: m_position(position),
	  m_onGameOver(onGameOver)
{
}

void GameCore::SeaDeepest::Draw() const
{
	m_texture.fitted(Scene::Size()).draw(m_position + Vec2{0, -420});
}

void GameCore::SeaDeepest::Reset()
{
	m_health = m_initHealth;
}

void GameCore::SeaDeepest::TakeOnAttack(int takeAttackPower)
{
	m_health -= takeAttackPower;

	if (m_health <= 0)
	{
		m_onGameOver();
	}
}
