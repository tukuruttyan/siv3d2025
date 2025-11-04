#pragma once
#include <array>
#include "CreatureBasicParam.h"
#include "TrashEnemyAnimation.h"

namespace GameCore::EnemyParams
{
	enum class TrashEnemyType : std::size_t {
		Akikan = 0,
		Taiya,
		Bag,
		_Count
	};

	// --- Lazy getters ---
	inline const std::array<CreatureBasicParam,
		static_cast<std::size_t>(TrashEnemyType::_Count)>& TrashEnemyParams()
	{
		static const std::array<CreatureBasicParam,
			static_cast<std::size_t>(TrashEnemyType::_Count)> kParams = {
			/* Akikan */ CreatureBasicParam{0.5f, 1.5f, 0.2f, 0.2f, 2, 1, 3, 0,  40.0f, 0, s3d::Vec2{100, 100}},
			/* Taiya  */ CreatureBasicParam{0.5f, 1.5f, 0.2f, 0.2f, 2, 1, 3, 0,  10.0f, 0, s3d::Vec2{100, 100}},
			/* Bag    */ CreatureBasicParam{0.5f, 1.5f, 0.2f, 0.2f, 2, 1, 3, 0, 100.0f, 0, s3d::Vec2{200, 200}},
		};
		return kParams;
	}

	inline const std::array<TrashEnemyAnimation,
		static_cast<std::size_t>(TrashEnemyType::_Count)>& TrashEnemyAnims()
	{
		static const std::array<TrashEnemyAnimation,
			static_cast<std::size_t>(TrashEnemyType::_Count)> kAnims = {
			/* Akikan */
			TrashEnemyAnimation{
				SpriteAnimation{ U"images/Enemy/Akikan.png", 3, 1, 1.0f },
				SpriteAnimation{ U"images/Enemy/Akikan.png", 3, 1, 1.0f },
				s3d::Vec2{100, 100}
			},
			/* Taiya */
			TrashEnemyAnimation{
				SpriteAnimation{ U"images/Enemy/TaiyaAttack.png", 12, 1, 3.0f },
				SpriteAnimation{ U"images/Enemy/TaiyaAttack.png", 12, 1, 3.0f },
				s3d::Vec2{100, 100}
			},
			/* Bag */
			TrashEnemyAnimation{
				SpriteAnimation{ U"images/Enemy/TrashBag.png", 12, 1, 4.0f },
				SpriteAnimation{ U"images/Enemy/TrashBag.png", 12, 1, 4.0f },
				s3d::Vec2{200, 200}
			}, };
		return kAnims;
	}
}
