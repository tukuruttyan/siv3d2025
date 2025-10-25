#include "stdafx.h"
#include "StageSelectPlayer.h"

void GameCore::StageSelectPlayer::update(const s3d::Vec2& targetPos)
{
	m_position = s3d::Math::Lerp(m_position, targetPos, 0.1);
}

void GameCore::StageSelectPlayer::draw()
{
	m_sprite.draw(m_position);
}
