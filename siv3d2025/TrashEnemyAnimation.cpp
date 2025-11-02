#include "stdafx.h"
#include "TrashEnemyAnimation.h"

GameCore::TrashEnemyAnimation::TrashEnemyAnimation(SpriteAnimation moveAnimation, SpriteAnimation attackingAnimation, Vec2 spriteSize)
	: m_moveAnimation	  (moveAnimation	 ),
	  m_attackingAnimation(attackingAnimation),
	  m_spriteSize		  (spriteSize		 )
{
}

void GameCore::TrashEnemyAnimation::Update(double deltaTime)
{
	if (m_alphaTimer > 0.0)
	{
		m_alphaTimer -= deltaTime;
		if (m_alphaTimer <= 0.0)
		{
			m_alphaTimer = 0.0;
			m_alphaValue = 1.0;
		}
	}
}

void GameCore::TrashEnemyAnimation::StartTransparent(float duration, double alpha)
{
	m_alphaDuration = duration;
	m_alphaTimer = duration;
	m_alphaValue = alpha;
}

void GameCore::TrashEnemyAnimation::DrawMove(const Vec2& position)
{
	const ScopedColorMul2D alphaMul(ColorF(1.0, m_alphaValue));
	m_moveAnimation.Draw(position, m_spriteSize);
}

void GameCore::TrashEnemyAnimation::DrawAttacking(const Vec2& position)
{
	const ScopedColorMul2D alphaMul(ColorF(1.0, m_alphaValue));
	m_attackingAnimation.Draw(position, m_spriteSize);
}
