#include "stdafx.h"
#include "KirimiButton.h"

using namespace s3d;


KirimiButton::KirimiButton(const Rect& rect, const ColorF& borderColor, const ColorF& normalColor,
	const ColorF& activeColor, const ColorF& disableColor, GameCore::CreatureBasicParam param, String icon) :
	m_rect(rect),
	m_normalColor(normalColor),
	m_activeColor(activeColor),
	m_disableColor(disableColor),
	m_borderColor(borderColor),
	m_param(param),
	m_icon(icon)
{
}

void KirimiButton::setSelected(bool selected)
{
	m_selected = selected;
}

// TODO: これ引数enable→selected
void KirimiButton::draw(GameCore::SpriteAnimation animation, bool selected, double resource) const
{
	//const bool disabled = !selected;

	// When cost is negative, draw only the icon with disabled background and border
	if (m_param.GetSpawnCost() < 0)
	{
		const RoundRect rr{ m_rect, 20 };
		rr.draw(m_disableColor);
		rr.drawFrame(0, 10, m_borderColor);

		const Vec2 center = rr.center();
		const Vec2 size{ rr.w - 20, rr.h - 20 };
		animation.Draw(center - size / 2, size);

		return;
	}

	ColorF fill = m_normalColor;
	//if (disabled) fill = m_disableColor;
	if (selected) fill = m_activeColor;
	else if (m_mouseOver) fill = m_disableColor;

	const RoundRect rr{ m_rect, 20 };
	rr.draw(fill);

	// リソースゲージ
	const double nextCostRatio = std::fmod(resource, m_param.GetSpawnCost()) / m_param.GetSpawnCost();
	const double h = rr.h * nextCostRatio;
	const RectF bottomRect{ rr.x, rr.y + (rr.h - h), rr.w, h };
	const auto clipped = Geometry2D::And(rr.asPolygon(), bottomRect.asPolygon());
	for (const auto& poly : clipped) {
		poly.draw(ColorF{ 1, 0.2 });
	}

	rr.drawFrame(0, 10, m_borderColor);

	const Vec2 center = rr.center();
	const Vec2 size{ rr.w - 20, rr.h - 20 };
	animation.Draw(center - size / 2, size);

	m_fontValue(Format(m_param.GetSpawnCost()))
		.draw(48, Arg::bottomCenter = Vec2{ rr.x + rr.w / 2, rr.y + rr.h }, m_borderColor);

	const int instanceCounts = static_cast<int>(resource / m_param.GetSpawnCost());
	m_fontValue(U"x" + Format(instanceCounts))
		.draw(32, Arg::topRight = Vec2{ rr.x + rr.w - 10, rr.y + 3 }, m_borderColor);


	if (m_mouseOver)
	{
		rr.drawShadow(Vec2{ 0, 2 }, 8, 1.0, ColorF{ 0, 0, 0, 0.15 });
	}
}
