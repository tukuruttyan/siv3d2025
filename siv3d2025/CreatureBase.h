#pragma once
#include "CreatureBasicParam.h"
#include <Siv3D.hpp>

namespace GameCore
{
	template<typename IAttackableT>
	class CreatureBase
	{
	public:
		explicit CreatureBase(CreatureBasicParam basicParam, s3d::Vec2 position);
		virtual ~CreatureBase() = default;

	private:
		static const int MIN_HEALTH = 0;
		CreatureBasicParam m_basicParam;
		s3d::Vec2 m_position;
		float m_attackDelayDuring_secs = 0.0f;
		float m_attackCooldownDuring_secs = 0.0f;
		CreatureState m_state = CreatureState::Moving;

	protected:
		virtual s3d::Vec2 MoveDirection() const = 0;

		//NOTE: 以下サンドボックスパターン
		s3d::RectF HitBoxColliderRect() const { return { m_position, m_basicParam.GetColliderSize() }; }
		std::vector<IAttackableT*> CatchInAttackAreaTarget(const std::vector<IAttackableT*>& attackables) const;
		void DrawDebug() const;
		const s3d::Vec2& GetPosition() const { return m_position; }
		CreatureBasicParam& BasicParam() { return m_basicParam; }
		const CreatureState& GetState() const { return m_state; }
		void UpdateMoveState(const std::vector<IAttackableT*>& attackables);
		void UpdateAttackingState(const std::vector<IAttackableT*>& attackables);
		void UpdateAttackCooldownState(const std::vector<IAttackableT*>& attackables);
		void OnDamage(int takeAttackPower);
		bool CheckOnDeath();
	};

	template<typename IAttackableT>
	inline CreatureBase<IAttackableT>::CreatureBase(CreatureBasicParam basicParam, s3d::Vec2 position)
		: m_basicParam(basicParam), m_position(position) {
	}

	template<typename IAttackableT>
	inline void CreatureBase<IAttackableT>::UpdateMoveState(const std::vector<IAttackableT*>& attackables)
	{
		m_position += MoveDirection() * m_basicParam.GetMoveSpeed() * s3d::Scene::DeltaTime();

		const auto targets = CatchInAttackAreaTarget(attackables);
		if (!targets.empty())
		{
			targets.front()->TakeOnAttack(m_basicParam.GetAttackPower());
			m_state = CreatureState::UpdateAttackingState;
		}
	}

	template<typename IAttackableT>
	inline void CreatureBase<IAttackableT>::UpdateAttackingState(const std::vector<IAttackableT*>& attackables)
	{
		m_attackDelayDuring_secs += s3d::Scene::DeltaTime();

		if (m_attackDelayDuring_secs < m_basicParam.GetAttackDelay_secs())
			return;

		const auto targets = CatchInAttackAreaTarget(attackables);
		if (!targets.empty())
		{
			targets.front()->TakeOnAttack(m_basicParam.GetAttackPower());
			m_attackDelayDuring_secs = 0.0f;
			m_state = CreatureState::UpdateAttackCooldownState;
		}
	}

	template<typename IAttackableT>
	inline void CreatureBase<IAttackableT>::UpdateAttackCooldownState(const std::vector<IAttackableT*>& attackables)
	{
		m_attackCooldownDuring_secs += s3d::Scene::DeltaTime();

		if (m_attackCooldownDuring_secs < m_basicParam.GetAttackCooldown_secs())
			return;

		m_attackCooldownDuring_secs = 0.0f;

		const auto targets = CatchInAttackAreaTarget(attackables);
		m_state = targets.empty() ? CreatureState::Moving : CreatureState::UpdateAttackingState;
	}

	template<typename IAttackableT>
	inline void CreatureBase<IAttackableT>::OnDamage(const int takeAttackPower)
	{
		m_basicParam = m_basicParam.WithOnDamage(takeAttackPower);
	}

	template<typename IAttackableT>
	inline bool CreatureBase<IAttackableT>::CheckOnDeath()
	{
		return MIN_HEALTH >= BasicParam().GetHealth();
	}

	template<typename IAttackableT>
	inline std::vector<IAttackableT*> CreatureBase<IAttackableT>::CatchInAttackAreaTarget(const std::vector<IAttackableT*>& attackables) const
	{
		const double attackRangeY = m_basicParam.GetAttackRange();
		const s3d::RectF attackAreaY
		{
			m_position.x - 10000.0,
			m_position.y,
			20000.0,
			attackRangeY
		};

		std::vector<IAttackableT*> candidates;

		for (auto* attackable : attackables)
		{
			if (attackable && attackAreaY.intersects(attackable->ColliderRect()))
			{
				if (std::find(candidates.begin(), candidates.end(), attackable) == candidates.end())
				{
					candidates.push_back(attackable);
				}
			}
		}

		std::sort(candidates.begin(), candidates.end(),
			[this](IAttackableT* a, IAttackableT* b)
			{
				const double distA2 = (a->ColliderRect().center() - m_position).lengthSq();
				const double distB2 = (b->ColliderRect().center() - m_position).lengthSq();
				return distA2 < distB2;
			});

		if (candidates.size() > m_basicParam.GetAttackTargetNumber())
		{
			candidates.resize(m_basicParam.GetAttackTargetNumber());
		}

		return candidates;
	}

	template<typename IAttackableT>
	inline void CreatureBase<IAttackableT>::DrawDebug() const
	{
		HitBoxColliderRect().drawFrame(2.0, 2.0, Palette::Green);
		const s3d::RectF attackArea{ m_position, s3d::Vec2{ m_basicParam.GetAttackRange(), m_basicParam.GetAttackRange() } };
		attackArea.drawFrame(2.0, 2.0, Palette::Red);
	}
}
