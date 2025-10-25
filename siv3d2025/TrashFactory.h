#include "SpawnCooldown.h"
#include "TrashEnemy.h"

namespace GameCore
{
	class TrashFactory final
	{
	public:
		explicit TrashFactory(std::vector<std::pair<SpawnCooldown, TrashEnemy>> spawnEnemies, s3d::Vec2 position);

		void Tick();
		void Draw();

	private:
		std::vector<std::pair<SpawnCooldown, TrashEnemy>> m_spawnEnemies;
		Vec2 m_position;
	};
}
