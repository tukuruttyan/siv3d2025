#pragma once
#include "DeepSeaFish.h"

namespace GameCore
{
	class SeaDeepest final : public ITakableTrashEnemyAttack
	{
	public:
		SeaDeepest(Vec2 position);
		void Update(const std::function<void(DeepSeaFish)>& addSceneDeepSeaFish, const std::function<void(DeepSeaFish&)>& removeSceneDeepSeaFish);
		void Draw() const;

	private:
		void TakeOnAttack(int takeAttackPower) override;
		s3d::RectF ColliderRect() override
		{
			return s3d::RectF(m_position, 100, 100);
		}

		s3d::Texture m_texture{ U"example/windmill.png" };
		s3d::Vec2 m_position{ -100, 0 };
		int m_health = 40;
	};
}
