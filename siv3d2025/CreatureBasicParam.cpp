#include "stdafx.h"
#include "CreatureBasicParam.h"

GameCore::CreatureBasicParam::CreatureBasicParam(float weight, float attackRange, float attackDelay_secs, float attackCooldown_secs, int attackPower, int attackTargetNumber, int health, int defensePower, float moveSpeed, int spawnCost, s3d::Vec2 colliderSize, SpriteAnimation movingAnimation, SpriteAnimation attackingAnimation)
	: m_weight			   (weight				)
	, m_attackRange		   (attackRange			)
	, m_attackDelay_secs   (attackDelay_secs	)
	, m_attackCooldown_secs(attackCooldown_secs	)
	, m_attackPower		   (attackPower			)
	, m_attackTargetNumber (attackTargetNumber	)
	, m_health			   (health				)
	, m_defensePower	   (defensePower		)
	, m_moveSpeed		   (moveSpeed			)
	, m_spawnCost          (spawnCost			)
	, m_colliderSize       (colliderSize		)
	, m_movingAnimation	   (movingAnimation		)
	, m_attackingAnimation (m_attackingAnimation)
{
}
