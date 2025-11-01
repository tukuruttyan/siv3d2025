#pragma once
#include "Kirimi.h"
#include "ITakableTrashEnemyAttack.h"
#include "ITakableSeaFishAttack.h"
#include "CreatureBase.h"

namespace GameCore
{
	class DeepSeaFish final : public CreatureBase<ITakableSeaFishAttack>, public ITakableTrashEnemyAttack
	{
	public:
		explicit DeepSeaFish(const std::vector<Kirimi>& kirimis, s3d::Vec2 position, const std::function<void(DeepSeaFish&)> removeSceneFish);
		void Update(const std::vector<ITakableSeaFishAttack*>& attackables);
		void Draw();

	private:
		CreatureBasicParam CombineKirimiParam(const std::vector<Kirimi>& kirimis);

		Vec2 MoveDirection() const override { return s3d::Vec2::Up(); }
		RectF ColliderRect() override { return HitBoxColliderRect(); }
		void TakeOnAttack(int attackPower) override;

		std::vector<Kirimi> m_kirimis;
		std::function<void(DeepSeaFish&)> m_removeSceneFish;
	};
}
