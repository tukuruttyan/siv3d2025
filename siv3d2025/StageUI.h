#pragma once
#include <Siv3D.hpp>

class KirimiButton;
// 独自ボタン: 正方形、ラベル2つ（コスト、可能個数）、選択/非選択の切り替え
// 使い方の例:
//   KirimiButton btn({50, 50}, 80, 12);        // 位置(50,50)、辺80px、コスト12
//   btn.setAvailableCount(3);
//   btn.update();
//   btn.draw();
//   if (btn.pressed()) { /* クリック直後のトグルを検知 */ }
class StageUI
{
public:
	StageUI();
	void Reset();
	void SetCosts(std::array<int, 8> costs);
	void update(double deltaTime) const;
	void draw(double deltaTime, double resource, double scroll) const;

private:
	// Precompute static geometry (polygons) once and reuse at draw time
	void precomputeGeometry();

	void drawLeftSide(double deltaTime, double resource, double scroll) const;
	void drawRightSide(double deltaTime, double resource, double scroll) const;

	void drawChart(double scroll) const;
	void drawMinimap(double scroll) const;
	void drawKirimiPalette(double resource) const;
	void drawKimeraCanvas() const;

	// Cached UI elements
	Polygon m_minimapFrameCutout;   // frameRect - mainRect
	Polygon m_minimapShadowCutout;  // shadowRect - frameRect
	Polygon m_minimapBuildingClip;  // union of building parts
	Polygon m_minimapMarineClip;    // union of marine parts
	Polygon m_kimeraHandleUnion;    // union of handleBase & handleTip

	std::vector<KirimiButton> m_kirimiButtons;

	const ColorF m_baseColor { Palette::Dimgray };
	const ColorF m_mainColor { Palette::Slategray };
	const ColorF m_accentColor { Palette::Lightsteelblue };
	const ColorF m_subColor { Palette::Black };
	const ColorF m_shadowColor { Palette::Black, 0.3 };
	const ColorF m_canvasColor{ Palette::White, 0.3 };
	const ColorF m_canvasFadeOutColor{ Palette::Slategray, 0.2 };
	const ColorF m_canvasFadeInColor{ Palette::Slategray, 0 };

	Font m_deepLabel{ 14 };
	Font m_propLabel{ 18 };
	Font m_resourceLabel{ 18 };
};
