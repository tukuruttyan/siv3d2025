#include "stdafx.h"
#include "SpriteAnimation.h"

GameCore::SpriteAnimation::SpriteAnimation(const FilePath& path, int cols, int rows, double totalTime_secs)
	: texture(path),
	  columns(cols),
	  rows(rows),
	  totalFrames(cols* rows),
	  totalTime_secs(totalTime_secs)
{
	if (not texture)
	{
		Print << path << U" の読み込みに失敗しました";
	}
}

void GameCore::SpriteAnimation::Draw(const Vec2& pos)
{
	time += Scene::DeltaTime();
	if (time > totalTime_secs)
	{
		time -= totalTime_secs;
	}

	const int frame = static_cast<int>((time / totalTime_secs) * totalFrames) % totalFrames;
	const int col = frame % columns;
	const int row = frame / columns;

	const double u = static_cast<double>(col) / columns;
	const double v = static_cast<double>(row) / rows;
	const double uSize = 1.0 / columns;
	const double vSize = 1.0 / rows;

	texture.uv(u, v, uSize, vSize).draw(pos);
}

void GameCore::SpriteAnimation::Draw(const Vec2& pos, const SizeF& size)
{
	time += Scene::DeltaTime();
	if (time > totalTime_secs)
	{
		time -= totalTime_secs;
	}

	const int frame = static_cast<int>((time / totalTime_secs) * totalFrames) % totalFrames;
	const int col = frame % columns;
	const int row = frame / columns;

	const double u = static_cast<double>(col) / columns;
	const double v = static_cast<double>(row) / rows;
	const double uSize = 1.0 / columns;
	const double vSize = 1.0 / rows;

	texture.uv(u, v, uSize, vSize).resized(size).draw(pos);
}
