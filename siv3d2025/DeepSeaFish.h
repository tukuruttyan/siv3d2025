#pragma once
#include "ITakableTrashEnemyAttack.h"
#include "ITakableSeaFishAttack.h"
#include "CreatureBase.h"

namespace GameCore
{
	class DeepSeaFish final : public CreatureBase<ITakableSeaFishAttack>, public ITakableTrashEnemyAttack
	{
	public:
		explicit DeepSeaFish(CreatureBasicParam basicParam, s3d::Vec2 position);
		void Update(const std::vector<ITakableSeaFishAttack*>& attackables);
		void Draw() ;

	private:
		s3d::Vec2 MoveDirection() const override { return s3d::Vec2::Up(); }
		s3d::RectF ColliderRect() override { return HitBoxColliderRect(); }
		void TakeOnAttack(int attackPower) override;
	};
}
