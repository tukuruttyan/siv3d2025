#pragma once
#include "CreatureBasicParam.h"

namespace GameCore::EnemyParams
{
#define DEFINE_TRASH_ENEMY_FUNC(NAME, ...) \
    static CreatureBasicParam NAME() { \
        static CreatureBasicParam param{ __VA_ARGS__ }; \
        return param; \
    }

	DEFINE_TRASH_ENEMY_FUNC(TRASH_BAG, 0.5f, 1.5f, 0.2f, 0.2f, 2, 1, 3, 0, 10.0f, 0, s3d::Vec2{ 100, 100 }, SpriteAnimation{ U"example/windmill.png", 1, 1, 10.0f }, SpriteAnimation{ U"example/windmill.png", 1, 1, 10.0f });
}
