#pragma once
#include "ITakableTrashEnemyAttack.h"
#include "ITakableSeaFishAttack.h"
#include "CreatureBase.h"

namespace GameCore
{
	class TrashEnemy final : public CreatureBase<ITakableTrashEnemyAttack>, public ITakableSeaFishAttack
	{
	public:
		explicit TrashEnemy(CreatureBasicParam basicParam, s3d::Vec2 position, const std::function<void(TrashEnemy&)> removeScene);
		void Update(const std::vector<ITakableTrashEnemyAttack*>& attackables);
		void Draw();

	private:
		s3d::Vec2 MoveDirection() const override { return s3d::Vec2::Down(); }
		s3d::RectF ColliderRect() override { return HitBoxColliderRect(); }
		void TakeOnAttack(int takeAttackPower) override;

		std::function<void(TrashEnemy&)> m_removeSceneTrashEnemy;
	};
}
