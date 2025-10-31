#include "StageUI.h"
#include "KirimiButton.h"

StageUI::StageUI()
{
	precomputeGeometry();
}

void StageUI::Init(std::shared_ptr<GameCore::StageSceneContext> context)
{
	m_context = context;

	m_kirimiButtons.clear();

	const auto costs = m_context->getCosts();
	generateKirimiButtons(costs);
}

void StageUI::update(double deltaTime, double resources, bool& canvasOpen) const
{
	if (MouseR.down()) // 右クリックが押されている間
	{
		canvasOpen = !canvasOpen;
	}

	for (const auto& button : m_kirimiButtons)
	{
		button.update();
	}

	updateLeftSide(deltaTime, resources, canvasOpen);
	updateRightSide();
}

void StageUI::updateLeftSide(double deltaTime, double resources, bool& canvasOpen) const
{
	Transformer2D t(Mat3x2::Translate(80, 100), TransformCursor::Yes);
	updateKimeraCanvas(deltaTime, canvasOpen);
	updateKirimiPalette(resources);
	for (const auto& button : m_kirimiButtons)
	{
		button.draw(resources);
	}
}
void StageUI::updateKirimiPalette(double resources) const
{
	drawKirimiPalette(resources);
}

void StageUI::updateKimeraCanvas(double deltaTime, bool& canvasOpen) const
{
	const auto ratio = canvasOpen ? 1 : 0;
	m_canvasWidth = Math::Lerp(m_canvasWidth, ratio * 1000, deltaTime * 10);
	const auto width = static_cast<int>(m_canvasWidth);

	Transformer2D t(Mat3x2::Translate({ 300, 25 }), TransformCursor::Yes);
	drawKimeraCanvas({width, 800});
	Transformer2D tHandle(Mat3x2::Translate({ width + 33, 0 }), TransformCursor::Yes);
	drawCanvasHandle(canvasOpen, 800);

	if (m_kimeraHandleUnion.leftClicked())
	{
		canvasOpen = !canvasOpen;
	}
}

void StageUI::updateRightSide() const
{
	Transformer2D t(Mat3x2::Translate(Scene::Width() - 480, 30), TransformCursor::Yes);
	updateChart();
	updateMinimap();
}


void StageUI::updateChart() const
{
	const int size = 200;
	Transformer2D t(Mat3x2::Translate({ size, size }), TransformCursor::Yes);

	drawChart(size);
}

void StageUI::updateMinimap() const
{
	Transformer2D baseT(Mat3x2::Translate({ 100, 430 }), TransformCursor::Yes);
	drawMinimap();
}


void StageUI::precomputeGeometry()
{
	// ====== Minimap constants (must match drawMinimap) ======
	const Size mainSize{ 180, 480 };
	const int mainCornerR = 30;
	const int outFrameSize = 15;
	const int inFrameSize = 40;
	const int frameRounded = 40;
	const int frameSize = outFrameSize + inFrameSize;
	const Point shadowOffset{ 40, 33 };

	// Frame and main rectangles
	const RoundRect mainRect{ frameSize, frameSize, mainSize , mainCornerR };
	const RoundRect frameRect{ outFrameSize, outFrameSize, mainSize.x + inFrameSize * 2, mainSize.y + inFrameSize * 2 , frameRounded };

	// Precompute: frame cutout = frameRect - mainRect
	{
		const auto framePolygon = frameRect.asPolygon();
		const auto cut = Geometry2D::Subtract(framePolygon, mainRect.asPolygon());
		m_minimapFrameCutout = cut.isEmpty() ? Polygon{} : cut[0];
	}

	// Precompute: shadow cutout = (frameRect moved by shadowOffset) - frameRect
	{
		const auto shadowRect = frameRect.movedBy(shadowOffset);
		const auto cut = Geometry2D::Subtract(shadowRect.asPolygon(), frameRect.asPolygon());
		m_minimapShadowCutout = cut.isEmpty() ? Polygon{} : cut[0];
	}

	// Precompute: building decoration union (coordinates relative to centered Transformer in draw)
	{
		const int scrollYSize = 120;
		const auto redLineY = -mainSize.y / 2 + scrollYSize - 5;
		RoundRect b01{ { -30, redLineY - 55 }, { 40, 55 }, 5 };
		RoundRect b02{ { -55, redLineY - 30 }, { 60, 30 }, 5 };
		RoundRect b03{ { 0, redLineY - 35 }, { 50, 35 }, 5 };
		RoundRect b04{ { 30, redLineY - 45 }, { 30, 45 }, 5 };

		const auto u1 = Geometry2D::Or(b01.asPolygon(), b02.asPolygon());
		const auto u2 = Geometry2D::Or(b03.asPolygon(), b04.asPolygon());
		const auto u = Geometry2D::Or(u1[0], u2[0]);
		m_minimapBuildingClip = u.isEmpty() ? Polygon{} : u[0];
	}

	// Precompute: marine decoration union (coordinates relative to centered Transformer in draw)
	{
		const auto greenLineY = mainSize.y / 2 - 20;
		RoundRect m01{ { -45, greenLineY - 45 }, { 80, 40 }, 20 };
		RoundRect m02{ { 30, greenLineY - 45 }, { 15, 40 }, 5 };
		RoundRect m03{ { -20, greenLineY - 65 }, { 25, 30 }, 5 };

		const auto u1 = Geometry2D::Or(m01.asPolygon(), m02.asPolygon());
		Polygon p12 = u1.isEmpty() ? Polygon{} : u1[0];
		const auto u = Geometry2D::Or(p12, m03.asPolygon());
		m_minimapMarineClip = u.isEmpty() ? Polygon{} : u[0];
	}

	// ====== Kimera canvas handle union (static size) ======
	{
		const int height = 850;
		RoundRect handleBase{ 0, 0, 65, height, 15 };
		RoundRect handleTip{ 50, 50, 50, height - 100, 15 };
		const auto u = Geometry2D::Or(handleBase.asPolygon(), handleTip.asPolygon());
		m_kimeraHandleUnion = u.isEmpty() ? Polygon{} : u[0];
	}
}


void StageUI::generateKirimiButtons(std::array<int, 8> costs)
{
	const std::array<String, 8> buttonIcons{ U"い", U"ろ", U"は", U"に", U"ほ", U"へ", U"と", U"ち" };

	const int buttonSize = 125;
	const int buttonMargin = 30;
	const int buttonDiff = buttonSize + buttonMargin;

	const Point baseOffset{ 30, 60 };
	for (int i = 0; i < costs.size(); i++)
	{
		const auto xLane = static_cast<int>(i / 4);
		const Point pos{
			xLane * buttonDiff,
			i % 4 * buttonDiff
		};
		m_kirimiButtons.push_back(KirimiButton{ Rect{ baseOffset + pos, buttonSize }, m_subColor, m_mainColor, m_accentColor, m_baseColor, costs[i], buttonIcons[i]});
	}
	m_kirimiButtons[0].setSelected(true);
}

void StageUI::drawKimeraCanvas(Size size) const
{
	// Canvas
	size.x += 50;
	Rect { 0, 0, size }.draw(m_canvasColor);
	const int fadeLength = 20;
	Rect { 0, 0, size.x, fadeLength }.draw(Arg::top(m_canvasFadeOutColor), Arg::bottom(m_canvasFadeInColor));
	Rect { 0, size.y - fadeLength, size.x, fadeLength }.draw(Arg::top(m_canvasFadeInColor), Arg::bottom(m_canvasFadeOutColor));
}

void StageUI::drawCanvasHandle(bool canvasOpen, int height) const
{
	// Handle
	m_kimeraHandleUnion.draw(m_baseColor);
	m_kimeraHandleUnion.drawFrame(15, m_subColor);

	// Handle Arrows
	Transformer2D tArrow(Mat3x2::Translate({ 60, height/2 }), TransformCursor::Yes);

	Line { 0, 120, 0, 300 }.draw(LineStyle::RoundCap, 10, m_shadowColor);
	Line { 0, -120, 0, -300 }.draw(LineStyle::RoundCap, 10, m_shadowColor);


	Line { -15, 60, 15, 0 }.draw(LineStyle::RoundCap, 10, m_mainColor);
	Line { -15, -60, 15, 0 }.draw(LineStyle::RoundCap, 10, m_mainColor);
	Line { -15, 0, 15, 60 }.draw(LineStyle::RoundCap, 10, m_mainColor);
	Line { -15, 0, 15, -60 }.draw(LineStyle::RoundCap, 10, m_mainColor);

	if (canvasOpen)
	{
		Line { -15, 0, 15, 60 }.draw(LineStyle::RoundCap, 10, m_accentColor);
		Line { -15, 0, 15, -60 }.draw(LineStyle::RoundCap, 10, m_accentColor);
	}else
	{
		Line { -15, 60, 15, 0 }.draw(LineStyle::RoundCap, 10, m_accentColor);
		Line { -15, -60, 15, 0 }.draw(LineStyle::RoundCap, 10, m_accentColor);
	}
}

void StageUI::drawKirimiPalette(double resources) const
{
	RoundRect{ 0, 0, 350, 900, 50 }.draw(m_baseColor).drawFrame(0, 15, m_subColor);

	RoundRect{ 30, 800, 290, 75, 20 }.draw(m_baseColor).drawFrame(0, 10, m_subColor);

	const auto txt =

	m_resourceLabel(U"{:0>9}"_fmt(static_cast<int>(resources))).drawAt(50, { 174, 835 }, m_subColor);
}


void StageUI::drawChart(int size) const
{
	const int outFrameSize = 15;
	const int inFrameSize = 40;

	Circle frameRect{ size };
	Circle contentRect{ size - inFrameSize };

	frameRect.draw(m_baseColor);
	frameRect.drawFrame(0, outFrameSize, m_subColor);
	contentRect.draw(m_mainColor);


	Circle{ 10 }.draw(m_shadowColor);
	Circle{ 40 }.drawFrame(3, m_shadowColor);
	Circle{ 80 }.drawFrame(3, m_shadowColor);
	Circle{ 120 }.drawFrame(3, m_shadowColor);

	Line{ {-160, 0}, {160, 0 } }.draw(3, m_shadowColor);
	Line{ {0, -160}, {0, 160 } }.draw(3, m_shadowColor);

	contentRect.drawFrame(30, 0, ColorF{ 0, 0.0 }, m_shadowColor);
}

void StageUI::drawMinimap() const
{
	// Validate
	const Size mainSize{ 180, 480 };
	const int mainCornerR = 30;

	const int outFrameSize = 15;
	const int inFrameSize = 40;
	const int frameRounded = 40;

	const int frameSize = outFrameSize + inFrameSize;

	const Point shadowOffset{ 40, 33 };


	// Geometry
	const RoundRect mainRect{ frameSize, frameSize, mainSize , mainCornerR };

	const RoundRect frameRect{ outFrameSize, outFrameSize, mainSize.x + inFrameSize * 2, mainSize.y + inFrameSize * 2 , frameRounded };

	// frame
	frameRect.drawFrame(0, outFrameSize, m_subColor);

	m_minimapFrameCutout.draw(m_baseColor);

	// main
	mainRect.draw(m_canvasColor);

	// shadows
	m_minimapShadowCutout.draw(m_shadowColor);

	Transformer2D mainT(Mat3x2::Translate({ frameSize + mainSize.x / 2, frameSize + mainSize.y / 2 }), TransformCursor::Yes);
	// deco
	const int scrollYSize = 120;
	const auto greenLineY = mainSize.y / 2 - 20;
	const auto redLineY = -mainSize.y / 2 + scrollYSize - 5;
	const auto lineX = mainSize.x / 2 - 8;
	Line{ { -lineX, greenLineY }, { lineX, greenLineY } }.draw(5, Palette::Green);
	Line{ { -lineX, redLineY }, { lineX, redLineY } }.draw(5, Palette::Red);

	// Precomputed building decoration
	m_minimapBuildingClip.drawFrame(5, Palette::Red);

	Circle{ 8, redLineY - 70, 5 }.drawFrame(5, Palette::Red);
	Circle{ 15, redLineY - 90, 7 }.drawFrame(5, Palette::Red);

	 // Precomputed marine decoration
	 m_minimapMarineClip.drawFrame(5, Palette::Green);

	// fades
	Circle fadeCornerRect{ mainCornerR };
	const Point mainCenter{ mainSize.x / 2 - mainCornerR, mainSize.y / 2 - mainCornerR };
	fadeCornerRect.movedBy({ mainCenter.x, -mainCenter.y }).drawPie(0_deg, 90_deg, m_canvasFadeInColor, m_canvasFadeOutColor);
	fadeCornerRect.movedBy({ mainCenter.x, mainCenter.y }).drawPie(90_deg, 90_deg, m_canvasFadeInColor, m_canvasFadeOutColor);
	fadeCornerRect.movedBy({ -mainCenter.x, mainCenter.y }).drawPie(180_deg, 90_deg, m_canvasFadeInColor, m_canvasFadeOutColor);
	fadeCornerRect.movedBy({ -mainCenter.x, -mainCenter.y }).drawPie(270_deg, 90_deg, m_canvasFadeInColor, m_canvasFadeOutColor);

	Rect{ -mainCenter.x, -mainCenter.y - mainCornerR, mainSize.x - mainCornerR * 2, mainCornerR }.draw(Arg::top(m_canvasFadeOutColor), Arg::bottom(m_canvasFadeInColor));
	Rect{ -mainCenter.x, mainCenter.y, mainSize.x - mainCornerR * 2, mainCornerR }.draw(Arg::top(m_canvasFadeInColor), Arg::bottom(m_canvasFadeOutColor));
	Rect{ -mainCenter.x - mainCornerR, -mainCenter.y, mainCornerR, mainSize.y - mainCornerR * 2 }.draw(Arg::left(m_canvasFadeOutColor), Arg::right(m_canvasFadeInColor));
	Rect{ mainCenter.x, -mainCenter.y, mainCornerR, mainSize.y - mainCornerR * 2 }.draw(Arg::left(m_canvasFadeInColor), Arg::right(m_canvasFadeOutColor));

	// scroll
	const int margin = 15;
	Point decoSize{ mainSize.x - margin, 120 };
	Transformer2D scrollT(Mat3x2::Translate({ 0, (mainSize.y - decoSize.y - margin) * (0.5 - 1)}), TransformCursor::Yes);
	RoundRect{ -decoSize / 2, decoSize, mainCornerR - 4 }.drawFrame(5, m_accentColor);
	Line{ { -10, 0 }, { 10, 0 } }.draw(5, m_accentColor);
	Line{ { 0, -10 }, { 0, 10 } }.draw(5, m_accentColor);
}

