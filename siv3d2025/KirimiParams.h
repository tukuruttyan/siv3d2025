#pragma once
#include <array>
#include "CreatureBasicParam.h"
#include "SpriteAnimation.h"

namespace GameCore::EnemyParams
{
	enum class KirimiType : std::size_t {
		Empty = 0,
		FishEye,
		SharpFin,
		FlatFin,
		SquareBody,
		TryangleBody,
		ThornMouth,
		_Count
	};

	// --- Lazy getters ---
	inline const std::array<CreatureBasicParam,
		static_cast<std::size_t>(KirimiType::_Count)>& KirimiParams()
	{
		static const std::array<CreatureBasicParam,
			static_cast<std::size_t>(KirimiType::_Count)> kParams = {
			/* Empty        */ CreatureBasicParam{0,     0,   0,   0, 0, 0, 0, 0,   0,  -1, s3d::Vec2{0, 0}},
			/* FishEye      */ CreatureBasicParam{0.2f,  2.5f,0.5f,1, 0, 1.3f, 0, 0, 0,  25, s3d::Vec2{100, 100}},
			/* SharpFin     */ CreatureBasicParam{0.5f,  1.0f,0.3f,1, 1, 1.0f, 1, 0, 1.5f,80, s3d::Vec2{100, 100}}, // スルドイヒレ
			/* FlatFin      */ CreatureBasicParam{0.2f,  0.5f,0.5f,1, 0, 0.0f, 1, 0, 2.5f,50, s3d::Vec2{100, 100}}, // タイラナヒレ
			/* SquareBody   */ CreatureBasicParam{7.0f,  1.0f,0.5f,1.5f,0, 0.0f, 5, 5, 0.0f,60, s3d::Vec2{100, 100}}, // ハガネノウロコ（■）
			/* TryangleBody */ CreatureBasicParam{1.5f,  1.0f,0.5f,0.5f,0, 1.0f, 3, 1, 2.5f,40, s3d::Vec2{100, 100}}, // スマートナカラダ（△）
			/* ThornMouth   */ CreatureBasicParam{0.5f,  1.0f,0.3f,1,8, 3, 1, 1, 0,50, s3d::Vec2{0, 0}}
		};
		return kParams;
	}

	inline const std::array<SpriteAnimation,
		static_cast<std::size_t>(KirimiType::_Count)>& KirimiAnims()
	{
		static const std::array<SpriteAnimation,
			static_cast<std::size_t>(KirimiType::_Count)> kAnims = {
			/* Empty        */ SpriteAnimation{ U"images/Kirimi/Empty.png",        3, 1, 1.0f },
			/* FishEye      */ SpriteAnimation{ U"images/Kirimi/FishEye.png",      3, 1, 1.0f },
			/* SharpFin     */ SpriteAnimation{ U"images/Kirimi/SharpFin.png",     3, 1, 1.0f },
			/* FlatFin      */ SpriteAnimation{ U"images/Kirimi/FlatFin.png",      3, 1, 1.0f },
			/* SquareBody   */ SpriteAnimation{ U"images/Kirimi/SquareBody.png",   3, 1, 1.0f },
			/* TryangleBody */ SpriteAnimation{ U"images/Kirimi/TryangleBody.png", 3, 1, 1.0f },
			/* ThornMouth   */ SpriteAnimation{ U"images/Kirimi/ThornMouth.png", 3, 1, 1.0f }
		};
		return kAnims;
	}
}
