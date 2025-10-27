#pragma once
#include "DeepSeaFish.h"

namespace GameCore
{
	class SeaDeepest final
	{
	public:
		void Update(std::function<void(DeepSeaFish)> addSceneDeepSea);
		void Draw() const;

	private:
		s3d::Texture m_texture{ U"example/windmill.png" };
		s3d::Vec2 m_position{ 0, 0 };
	};
}
