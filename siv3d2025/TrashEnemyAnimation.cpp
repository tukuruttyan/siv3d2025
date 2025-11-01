#include "stdafx.h"
#include "TrashEnemyAnimation.h"

GameCore::TrashEnemyAnimation::TrashEnemyAnimation(SpriteAnimation moveAnimation, SpriteAnimation attackingAnimation, Vec2 spriteSize)
	: m_moveAnimation	  (moveAnimation	 ),
	  m_attackingAnimation(attackingAnimation),
	  m_spriteSize		  (spriteSize		 )
{
}

void GameCore::TrashEnemyAnimation::DrawMove(const Vec2& position)
{
	m_moveAnimation.Draw(position, m_spriteSize);
}

void GameCore::TrashEnemyAnimation::DrawAttacking(const Vec2& position)
{
	m_attackingAnimation.Draw(position, m_spriteSize);
}
