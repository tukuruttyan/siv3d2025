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

		void StartTransparent(float duration, double alpha = 0.5);
		void Update(double deltaTime);

	private:
		SpriteAnimation m_moveAnimation;
		SpriteAnimation m_attackingAnimation;
		Vec2 m_spriteSize;

		double m_alphaTimer = 0.0;
		double m_alphaDuration = 0.0;
		double m_alphaValue = 1.0;
	};
}
