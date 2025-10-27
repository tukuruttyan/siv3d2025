#pragma once
namespace GameCore
{
	class ITakableTrashEnemyAttack
	{
	public:
		virtual ~ITakableTrashEnemyAttack() = default;
		virtual void TakeOnAttack(int takeAttackPower) = 0;
		virtual s3d::RectF ColliderRect() = 0;
	};
}
