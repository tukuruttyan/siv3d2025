#pragma once
namespace GameCore
{
	class ITakableSeaFishAttack
	{
	public:
		virtual ~ITakableSeaFishAttack() = default;
		virtual void TakeOnAttack(int attackPower) = 0;
		virtual s3d::RectF ColliderRect() = 0;
	};
}
