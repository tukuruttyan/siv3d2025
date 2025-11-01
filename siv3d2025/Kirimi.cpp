#include "stdafx.h"
#include "Kirimi.h"

void GameCore::Kirimi::Draw(const Vec2& offsetPos)
{
	m_animation.Draw(offsetPos + m_position, Vec2{ m_size,m_size }, m_rotate);
}
