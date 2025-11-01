#pragma once
#include "CreatureBasicParam.h"

namespace GameCore::EnemyParams
{
#define DEFINE_TRASH_ENEMY_FUNC(NAME, ...) \
    static CreatureBasicParam NAME() { \
        static CreatureBasicParam param{ __VA_ARGS__ }; \
        return param; \
    }

	DEFINE_TRASH_ENEMY_FUNC(TRASH_AKIKAN, 0.5f, 1.5f, 0.2f, 0.2f, 2, 1, 3, 0, 10.0f, 0, s3d::Vec2{ 100, 100 }, {100, 100}, SpriteAnimation{ U"Akikan.png", 3, 1, 1.0f }, SpriteAnimation{ U"Akikan.png", 3, 1, 1.0f });
	DEFINE_TRASH_ENEMY_FUNC(TRASH_TAIYA, 0.5f, 1.5f, 0.2f, 0.2f, 2, 1, 3, 0, 10.0f, 0, s3d::Vec2{ 100, 100 }, {100, 100}, SpriteAnimation{ U"TaiyaAttack.png", 12, 1, 1.0f }, SpriteAnimation{ U"TaiyaAttack.png", 12, 1, 1.0f });
}
