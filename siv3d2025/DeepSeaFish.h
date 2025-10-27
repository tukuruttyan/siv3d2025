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
		void Draw() const;

	private:
		s3d::RectF ColliderRect() override { return HitBoxColliderRect(); }
		void TakeOnAttack(int attackPower) override;
	};
}
