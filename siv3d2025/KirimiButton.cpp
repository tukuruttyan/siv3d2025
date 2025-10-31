#include "stdafx.h"
#include "KirimiButton.h"

using namespace s3d;


KirimiButton::KirimiButton(const Rect& rect, const ColorF& borderColor, const ColorF& normalColor,
	const ColorF& activeColor, const ColorF& disableColor, int cost, String icon) :
	m_rect(rect),
	m_normalColor(normalColor),
	m_activeColor(activeColor),
	m_disableColor(disableColor),
	m_borderColor(borderColor),
	m_cost(cost),
	m_icon(icon)
{
}

void KirimiButton::setSelected(bool selected)
{
	m_selected = selected;
}

// TODO: これ引数enable→selected
void KirimiButton::draw(bool enabled, double resource = 0) const
{
	const bool disabled = !enabled;

	// 背景色
	ColorF fill = m_normalColor;
	if (disabled) fill = m_disableColor;
	else if (m_selected) fill = m_activeColor; // selected中でもhover表示はうっすらでいいから出したい
	else if (m_mouseOver) fill = m_disableColor;

	const RoundRect rr{ m_rect, 20 };

	rr.draw(fill);

	// 下から ratio の割合で背景を重ねる
	double nextCostRatio = std::fmod(resource, m_cost) / m_cost;
	{
		const double h = rr.h * nextCostRatio;
		const RectF bottomRect{ rr.x, rr.y + (rr.h - h), rr.w, h };
		// rr の形状にクリップして描画
		const auto clipped = Geometry2D::And(rr.asPolygon(), bottomRect.asPolygon());
		for (const auto& poly : clipped)
		{
			poly.draw(ColorF{ 1, 0.2 });
		}
	}

	// 枠は最前面に描く
	rr.drawFrame(0, 10, m_borderColor);



	m_fontValue(Format(m_cost)).draw(48, Arg::bottomCenter = Vec2{ rr.x + rr.w / 2, rr.y + rr.h }, m_borderColor);

	int instanceCounts = static_cast<int>(resource / m_cost);
	String countsText = U"x" + Format(instanceCounts);
	m_fontValue(countsText).draw(32, Arg::topRight = Vec2 { rr.x + rr.w - 10, rr.y + 3 }, m_borderColor);


	m_fontValue(Format(m_icon)).draw(80, Arg::center= Vec2{ rr.x + rr.w / 2, rr.y + rr.h / 2 }, ColorF{ 0 });


	// ホバー時の影
	// TODO: 判定バグってる、治すこと(StageSceneUI参照
	if (m_mouseOver && !disabled)
	{
		rr.drawShadow(Vec2{ 0, 2 }, 8, 1.0, ColorF{ 0, 0, 0, 0.15 });
	}
}
