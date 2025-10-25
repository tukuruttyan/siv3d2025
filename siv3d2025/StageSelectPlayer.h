#pragma once
#include "vector"


namespace GameCore
{
	class StageSelectPlayer final
	{
	public:
		void update(const s3d::Vec2& targetPos);
		void draw();

	private:
		s3d::Vec2 m_position = s3d::Vec2{ 30, 30 };
		const Texture m_sprite{ U"example/windmill.png" };
	};
}
