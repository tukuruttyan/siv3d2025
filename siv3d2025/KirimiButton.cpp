#include "stdafx.h"
#include "KirimiButton.h"

using namespace s3d;

KirimiButton::KirimiButton(const Point& pos, int cost, String icon)
	: m_rect{ pos, 100 }
	, m_cost{ cost }
	, m_icon { icon }
{
}

void KirimiButton::setEnabled(bool enabled)
{
	m_enabled = enabled;
}

void KirimiButton::setSelected(bool selected)
{
	m_selected = selected;
}

bool KirimiButton::pressed() const
{
	const bool ret = m_justPressed;
	m_justPressed = false;
	return ret;
}

void KirimiButton::update()
{
	m_mouseOver = m_rect.mouseOver();
	m_justPressed = false;

	if (m_enabled)
	{
		if (m_rect.leftClicked())
		{
			m_selected = !m_selected;
			m_justPressed = true;
		}
	}
}

void KirimiButton::draw(float resource = 0) const
{
	const bool disabled = !m_enabled;

	// 背景色
	ColorF fill = disabled ? ColorF{ 0.75 } : (m_selected ? ColorF{ 0.80, 0.88, 1.0 } : ColorF{ 0.95 });
	if (m_mouseOver && !disabled)
	{
		fill = fill.lerp(ColorF{ 1.0 }, 0.12);
	}

	// 枠色
	const ColorF frame = disabled ? ColorF{ 0.5 } : (m_selected ? ColorF{ Palette::Dodgerblue } : ColorF{ 0.3 });

	const RoundRect rr{ m_rect, 20 };
	rr.draw(fill);

	// 下から ratio の割合で青色の背景を重ねる
	double nextCostRatio = std::fmod(resource, m_cost) / m_cost;
	{
		const double h = rr.h * nextCostRatio;
		const RectF bottomRect{ rr.x, rr.y + (rr.h - h), rr.w, h };
		// rr の形状にクリップして描画
		const auto clipped = Geometry2D::And(rr.asPolygon(), bottomRect.asPolygon());
		for (const auto& poly : clipped)
		{
			poly.draw(ColorF{ 0.75, 0.85, 1.0 }); // 青系
		}
	}

	// 枠は最前面に描く
	rr.drawFrame(3.0, 0.0, frame);



	m_fontValue(Format(m_cost)).draw(28, Arg::bottomCenter = Vec2{ rr.x + rr.w / 2, rr.y + rr.h }, ColorF{ 0 });

	int instanceCounts = static_cast<int>(resource / m_cost);
	String countsText = U"x" + Format(instanceCounts);
	m_fontValue(countsText).draw(20, Arg::topRight = Vec2 { rr.x + rr.w - 10, rr.y + 3 }, ColorF{0});


	m_fontValue(Format(m_icon)).draw(50, Arg::center= Vec2{ rr.x + rr.w / 2, rr.y + rr.h / 2 }, ColorF{ 0 });


	// ホバー時の影
	if (m_mouseOver && !disabled)
	{
		rr.drawShadow(Vec2{ 0, 2 }, 8, 1.0, ColorF{ 0, 0, 0, 0.15 });
	}
}
