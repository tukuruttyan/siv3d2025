#include "SpawnCooldown.h"
#include "TrashEnemy.h"
#include "OnSpawnTrashEnemy.h"

namespace GameCore
{
	class TrashFactory final : public ITakableSeaFishAttack
	{
	public:
		explicit TrashFactory(std::vector<OnSpawnTrashEnemy> spawnEnemies, int health);

		void Update(std::function<void(TrashEnemy)> addSceneTrashEnemy, const std::function<void(TrashEnemy&)>& removeSceneTrashEnemy);
		void Draw();

	private:
		void TakeOnAttack(int attackPower) override;
		s3d::RectF ColliderRect() override { return s3d::RectF(m_position, 100, 10); }

		std::vector<OnSpawnTrashEnemy> onSummonCreatures;
		const s3d::Vec2 m_position;
		const s3d::Texture m_texture{ U"example/windmill.png" };
		int m_health = 10;
	};
}
