#pragma once
#include "SpriteAnimation.h"

namespace GameCore
{
	class TrashEnemyAnimation final
	{
	public:
		explicit TrashEnemyAnimation(SpriteAnimation moveAnimation, SpriteAnimation attackingAnimation, Vec2 spriteSize);
		void DrawMove(const Vec2& position);
		void DrawAttacking(const Vec2& position);

	private:
		SpriteAnimation m_moveAnimation;
		SpriteAnimation m_attackingAnimation;
		Vec2 m_spriteSize;
	};
}
