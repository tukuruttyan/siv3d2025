#include "SpawnCooldown.h"
#include "TrashEnemy.h"

namespace GameCore
{
	class TrashFactory final
	{
	public:
		explicit TrashFactory(std::vector<std::pair<SpawnCooldown, const CreatureBasicParam>> spawnEnemies, s3d::Vec2 position);

		void Update(std::function<void(TrashEnemy)> addSceneTrashEnemy);
		void Draw();

	private:
		std::vector<std::pair<SpawnCooldown, const CreatureBasicParam>> m_summonCreatureParam;
		const s3d::Vec2 m_position;
		const s3d::Texture m_texture{ U"example/windmill.png" };
	};
}
