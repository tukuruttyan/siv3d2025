#pragma once
#include "DeepSeaFish.h"

namespace GameCore
{
	class SeaDeepest final
	{
	public:
		SeaDeepest(Vec2 position);
		void Update(const std::function<void(DeepSeaFish)>& addSceneDeepSeaFish, const std::function<void(DeepSeaFish&)>& removeSceneDeepSeaFish);
		void Draw() const;

	private:
		s3d::Texture m_texture{ U"example/windmill.png" };
		s3d::Vec2 m_position{ -100, 0 };
	};
}
