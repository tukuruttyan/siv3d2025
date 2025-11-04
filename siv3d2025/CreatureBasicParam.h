#pragma once
namespace GameCore
{
	enum CreatureState
	{
		Moving,
		UpdateAttackingState,
		UpdateAttackCooldownState
	};

	struct CreatureBasicParam final
	{
	public:
		CreatureBasicParam(float weight						 ,
						   float attackRange				 ,
						   float attackDelay_secs			 ,
						   float attackCooldown_secs		 ,
						   int   attackPower				 ,
						   float attackTargetNumber			 ,
						   int   health						 ,
						   int   defensePower				 ,
						   float moveSpeed					 ,
						   int   spawnCost					 ,
						   s3d::Vec2 colliderSize			 );

		[[nodiscard]] float			   GetWeight			 () const noexcept { return m_weight;			  }
		[[nodiscard]] float			   GetAttackRange		 () const noexcept { return m_attackRange;		  }
		[[nodiscard]] float			   GetAttackDelay_secs	 () const noexcept { return m_attackDelay_secs;	  }
		[[nodiscard]] float			   GetAttackCooldown_secs() const noexcept { return m_attackCooldown_secs;}
		[[nodiscard]] int			   GetAttackPower		 () const noexcept { return m_attackPower;		  }
		[[nodiscard]] float			   GetAttackTargetNumber () const noexcept { return m_attackTargetNumber; }
		[[nodiscard]] int			   GetHealth			 () const noexcept { return m_health;			  }
		[[nodiscard]] int			   GetDefensePower		 () const noexcept { return m_defensePower;		  }
		[[nodiscard]] float			   GetMoveSpeed			 () const noexcept { return m_moveSpeed;		  }
		[[nodiscard]] int			   GetSpawnCost			 () const noexcept { return m_spawnCost;		  }
		[[nodiscard]] s3d::Vec2		   GetColliderSize		 () const noexcept { return m_colliderSize;		  }

		CreatureBasicParam WithOnDamage(int damage) const;
		CreatureBasicParam operator+(const CreatureBasicParam& other) const
		{
			return CreatureBasicParam{
				m_weight + other.m_weight,
				m_attackRange + other.m_attackRange,
				m_attackDelay_secs - other.m_attackDelay_secs,
				m_attackCooldown_secs - other.m_attackCooldown_secs,
				m_attackPower + other.m_attackPower,
				m_attackTargetNumber + other.m_attackTargetNumber,
				m_health + other.m_health,
				m_defensePower + other.m_defensePower,
				m_moveSpeed + other.m_moveSpeed,
				m_spawnCost + other.m_spawnCost,
				m_colliderSize + other.m_colliderSize
			};
		}

	private:
		float m_weight				= 10.0f;
		float m_attackRange			= 10.0f;
		float m_attackDelay_secs	= 10.0f;
		float m_attackCooldown_secs = 10.0f;
		int   m_attackPower			= 10;
		float m_attackTargetNumber  = 10;
		int   m_health				= 10;
		int   m_defensePower		= 10;
		float m_moveSpeed			= 10.0f;
		int   m_spawnCost			= 10;
		Vec2 m_colliderSize    = { 100, 100 };
	};
}
