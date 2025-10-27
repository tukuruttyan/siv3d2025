#include "stdafx.h"
#include "SpriteAnimation.h"

GameCore::SpriteAnimation::SpriteAnimation(const FilePath& path, int cols, int rows, float totalTime_secs)
	: texture(path), columns(cols), rows(rows),
	totalFrames(cols* rows), totalTime_secs(totalTime_secs) {
}

void GameCore::SpriteAnimation::Update()
{
	time += Scene::DeltaTime();
	if (time > totalTime_secs)
	{
		time -= totalTime_secs;
	}
}

void GameCore::SpriteAnimation::Draw(const Vec2& pos) const
{
	int frame = static_cast<int>((time / totalTime_secs) * totalFrames) % totalFrames;
	int w = texture.width() / columns;
	int h = texture.height() / rows;
	int x = (frame % columns) * w;
	int y = (frame / columns) * h;
	texture(x, y, w, h).drawAt(pos);
}
