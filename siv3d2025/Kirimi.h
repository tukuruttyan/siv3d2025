#pragma once
#include "CreatureBasicParam.h"
#include "SpriteAnimation.h"

namespace GameCore
{
	class Kirimi final
	{
	public:
		Kirimi(const GameCore::CreatureBasicParam& param, double rotate, double size, const Point& position, SpriteAnimation animation)
			: m_param	 (param    )
			, m_rotate	 (rotate   )
			, m_size	 (size	   )
			, m_position (position )
			, m_animation(animation)
		{
		}

		const GameCore::CreatureBasicParam& GetParam() const { return m_param; }
		double GetRotate() const { return m_rotate; }
		double GetSize  () const { return m_size; }
		const Point& GetPosition() const { return m_position; }
		void Draw(const Vec2& offsetPos);

	private:
		GameCore::CreatureBasicParam m_param;
		double m_rotate;
		double m_size;
		Point m_position;
		SpriteAnimation m_animation;
	};
}
