#pragma once
#include <Siv3D.hpp>

// 独自ボタン: 正方形、ラベル2つ（コスト、可能個数）、選択/非選択の切り替え
// 使い方の例:
//   KirimiButton btn({50, 50}, 80, 12);        // 位置(50,50)、辺80px、コスト12
//   btn.setAvailableCount(3);
//   btn.update();
//   btn.draw();
//   if (btn.pressed()) { /* クリック直後のトグルを検知 */ }
class KirimiButton
{
	public:
		KirimiButton(const Rect& rect, const ColorF& borderColor, const ColorF& normalColor, const ColorF& activeColor, const ColorF& disableColor, int cost, String icon);

		void draw(bool enabled, double resource) const;

		[[nodiscard]] int cost() const { return m_cost; }
		[[nodiscard]] bool selected() const { return m_selected; }
		[[nodiscard]] bool mouseOver() const { return m_mouseOver; }
		[[nodiscard]] const Rect& rect() const { return m_rect; }

		void setSelected(bool selected);

	private:
		Rect m_rect{ 0, 0, 80, 80 };
		int m_cost = 100;
		String m_icon = U"へ";
		bool m_selected = false;
		mutable bool m_mouseOver = false;

		Font m_fontLabel{ 14 };
		Font m_fontValue{ 18 };

		const ColorF& m_normalColor;
		const ColorF& m_activeColor;
		const ColorF& m_disableColor;
		const ColorF& m_borderColor;
};
