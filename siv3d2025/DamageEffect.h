#pragma once
#include <Siv3D.hpp>

class DamageEffect : public IEffect
{
public:
	explicit DamageEffect(const Vec2& pos)
		: m_pos(pos)
	{
		for (int i = 0; i < 15; ++i)
		{
			const double angle = Random(0.0, Math::TwoPi);
			const double speed = Random(50.0, 150.0);
			m_particles.push_back({
				.pos = m_pos,
				.vel = Vec2(Cos(angle), Sin(angle)) * speed,
				.life = Random(0.3, 0.7)
			});
		}
	}

	bool update(double t) override
	{
		const double dt = Scene::DeltaTime();

		for (auto& p : m_particles)
		{
			p.life -= dt;
			p.pos += p.vel * dt;
			p.vel *= 0.9;
		}

		for (const auto& p : m_particles)
		{
			if (p.life > 0)
			{
				double alpha = Math::Saturate(p.life * 2.0);
				ColorF col(1.0, 0.2, 0.2, alpha);
				Circle(p.pos, 4).draw(col);
			}
		}

		return (t < 1.0);
	}

private:
	struct Particle
	{
		Vec2 pos;
		Vec2 vel;
		double life;
	};

	Vec2 m_pos;
	Array<Particle> m_particles;
};
