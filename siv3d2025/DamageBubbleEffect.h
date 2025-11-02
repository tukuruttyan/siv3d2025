# include <Siv3D.hpp>

struct DamageBubbleEffect : IEffect
{
	struct Bubble
	{
		Vec2 offset;
		double startTime;
		double scale;
		ColorF color;
	};

	Vec2 m_pos;
	Array<Bubble> m_bubbles;

	explicit DamageBubbleEffect(const Vec2& pos)
		: m_pos{ pos }
	{
		// 白・黒・赤を混ぜた「全体の基調色」を作成
		const ColorF mixedColor = MixColors();

		// 飛び散り量を控えめ（距離・個数を減らす）
		for (int32 i = 0; i < 5; ++i)
		{
			Bubble bubble{
				.offset = RandomVec2(Circle{ 20 }),
				.startTime = Random(-0.2, 0.1),
				.scale = Random(0.4, 1.0),
				.color = mixedColor // 全て同じ色調
			};
			m_bubbles << bubble;
		}
	}

	// 白・黒・赤をブレンドして統一トーンを作る（黒多め・赤少なめ）
	static ColorF MixColors()
	{
		// 白・黒・赤のブレンド比を調整（黒:多め、赤:控えめ）
		const double white = Random(0.2, 0.4);
		const double black = Random(0.5, 0.8);
		const double red = Random(0.1, 0.25);

		const double sum = white + black + red;

		const double r = (white * 1.0 + black * 0.0 + red * 1.0) / sum;
		const double g = (white * 1.0 + black * 0.0 + red * 0.0) / sum;
		const double b = (white * 1.0 + black * 0.0 + red * 0.0) / sum;

		return ColorF(r, g, b);
	}

	bool update(double t) override
	{
		for (const auto& bubble : m_bubbles)
		{
			const double t2 = (bubble.startTime + t);
			if (not InRange(t2, 0.0, 1.0))
			{
				continue;
			}

			const double e = EaseOutExpo(t2);

			Circle{
				m_pos + bubble.offset + (bubble.offset * 2 * t),
				e * 25 * bubble.scale
			}
				.draw(ColorF{ bubble.color, 0.18 })
				.drawFrame((15.0 * (1.0 - e) * bubble.scale), bubble.color);
		}

		return (t < 1.1);
	}
};
