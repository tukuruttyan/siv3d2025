#pragma once
#include <Siv3D.hpp>

#include "KirimiButton.h"
#include "StageSceneContext.h"

class StageUI
{
public:
	StageUI();
	void Init(std::shared_ptr<GameCore::StageSceneContext> context);
	void update(double deltaTime, double resources, bool& canvasOpen) const;

private:
	// Precompute static geometry (polygons) once and reuse at draw time
	void precomputeGeometry();
	void generateKirimiButtons(std::array<int, 8> costs);

	void updateLeftSide(double deltaTime, double resources, bool& canvasOpen) const;
	void updateRightSide() const;

	void updateChart() const;
	void updateMinimap() const;
	void updateKirimiPalette(double resources) const;
	void updateKimeraCanvas(double deltaTime, bool& canvasOpen) const;

	struct CanvasRects
	{
		Rect canvasRect;
		Array<Circle> propButtons;
		RoundRect spawnButton;
	};

	void drawChart(int size) const;
	void drawMinimap() const;
	void drawKirimiPalette(double resources) const;
	CanvasRects drawKimeraCanvas(Size size) const;
	void drawKirimiGhost() const;
	void drawDeepFish() const;
	void drawCanvasHandle(bool canvasOpen, int hegiht) const;

	// Scene context
	std::shared_ptr<GameCore::StageSceneContext> m_context;

	// Cached UI elements
	Polygon m_minimapFrameCutout;   // frameRect - mainRect
	Polygon m_minimapShadowCutout;  // shadowRect - frameRect
	Polygon m_minimapBuildingClip;  // union of building parts
	Polygon m_minimapMarineClip;    // union of marine parts
	mutable Polygon m_kimeraHandleUnion;    // union of handleBase & handleTip

	Array<KirimiButton> m_kirimiButtons;

	Font m_deepLabel{ 14 };
	Font m_propLabel{ 32, Typeface::Icon_MaterialDesign };
	Font m_spawnLabel{ 56 };
	Font m_resourceLabel{ 18 };

	// UI Colors
	const ColorF m_baseColor { Palette::Dimgray };
	const ColorF m_mainColor { Palette::Slategray };
	const ColorF m_accentColor { Palette::Lightsteelblue };
	const ColorF m_subColor { Palette::Black };
	const ColorF m_shadowColor { Palette::Black, 0.3 };
	const ColorF m_canvasColor{ Palette::White, 0.3 };
	const ColorF m_canvasFadeOutColor{ Palette::Slategray, 0.2 };
	const ColorF m_canvasFadeInColor{ Palette::Slategray, 0 };

	const Point m_shadowOffset{ 40, 33 };

	mutable double m_canvasWidth = 0;
	mutable int m_selectedKirimiIdx = 0;
	mutable double m_kirimiRotate = 0;
	mutable double m_kirimiSize = 100;
};
