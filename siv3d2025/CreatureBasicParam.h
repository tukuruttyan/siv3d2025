#pragma once
#include "SpriteAnimation.h"

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
						   int   attackTargetNumber			 ,
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
		[[nodiscard]] int			   GetAttackTargetNumber () const noexcept { return m_attackTargetNumber; }
		[[nodiscard]] int			   GetHealth			 () const noexcept { return m_health;			  }
		[[nodiscard]] int			   GetDefensePower		 () const noexcept { return m_defensePower;		  }
		[[nodiscard]] float			   GetMoveSpeed			 () const noexcept { return m_moveSpeed;		  }
		[[nodiscard]] int			   GetSpawnCost			 () const noexcept { return m_spawnCost;		  }
		[[nodiscard]] s3d::Vec2		   GetColliderSize		 () const noexcept { return m_colliderSize;		  }

		CreatureBasicParam WithOnDamage(int damage) const;

	private:
		float m_weight				= 10.0f;
		float m_attackRange			= 10.0f;
		float m_attackDelay_secs	= 10.0f;
		float m_attackCooldown_secs = 10.0f;
		int   m_attackPower			= 10;
		int   m_attackTargetNumber  = 10;
		int   m_health				= 10;
		int   m_defensePower		= 10;
		float m_moveSpeed			= 10.0f;
		int   m_spawnCost			= 10;
		s3d::Vec2 m_colliderSize    = { 100, 100 };
	};
}
