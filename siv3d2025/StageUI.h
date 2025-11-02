#pragma once
#include <Siv3D.hpp>
#include "CreatureBasicParam.h"
#include "SpriteAnimation.h"

#include "KirimiButton.h"
#include "StageSceneContext.h"


struct CanvasKirimi
{
	GameCore::CreatureBasicParam m_param;
	double rotate;
	double size;
	Point position;
	GameCore::SpriteAnimation m_animation;
};

class StageUI
{
	struct CanvasRects
	{
		Rect canvasRect;
		Array<Circle> propButtons;
		RoundRect spawnButton;
	};

public:
	StageUI();
	void Init(GameCore::StageSceneContext* context, std::function<void(Array<CanvasKirimi> fishProp)> onSpawned);
	void update(double deltaTime, double resources, bool& canvasOpen, std::function<void(std::type_index)> onChangeScene) const;
	void Reset() const;

private:
	// Precompute static geometry (polygons) once and reuse at draw time
	void precomputeGeometry();
	void generateKirimiButtons(const std::array<std::pair<const GameCore::SpriteAnimation, const GameCore::CreatureBasicParam>, 8>& kirimiInventory);

	void updateLeftSide(double deltaTime, double resources, bool& canvasOpen) const;
	void updateRightSide() const;

	void updateChart() const;
	void updateMinimap() const;
	void updateKirimiPalette(double resources) const;
	void updateKimeraCanvas(double deltaTime, bool& canvasOpen) const;

	void drawChart(int size) const;
	void drawMinimap() const;
	void drawKirimiPaletteShadow() const;
	void drawKirimiPalette(double resources) const;
	CanvasRects drawKimeraCanvas(Size size) const;
	void drawKirimiGhost() const;
	void drawDeepFish() const;
	void drawCanvasHandle(bool canvasOpen, int hegiht) const;
	const RoundRect& drawGame() const;

	void resetKirimiProp() const;

	// Scene context
	GameCore::StageSceneContext* m_context = nullptr;

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
	Font m_gameLabel{ 50 };

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

	mutable double m_gameScroll = 0;
	mutable double m_canvasWidth = 0;
	mutable int m_selectedKirimiIdx = 0;
	mutable double m_kirimiRotate = 0;
	mutable double m_kirimiSize = 100;
	mutable Array<CanvasKirimi> m_canvasKirimiArray;
	std::function<void(Array<CanvasKirimi> fishProp)> m_onSpawned;
};
