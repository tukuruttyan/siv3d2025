#include "stdafx.h"
#include "TrashEnemy.h"
#include <exception>

GameCore::TrashEnemy::TrashEnemy(CreatureBasicParam basicParam, s3d::Vec2 position, const std::function<void(TrashEnemy&)> removeSceneTrashEnemy)
	: CreatureBase(basicParam, position),
	  m_removeSceneTrashEnemy(removeSceneTrashEnemy)
{
}

void GameCore::TrashEnemy::Update(const std::vector<ITakableTrashEnemyAttack*>& attackables)
{
	switch (GetState())
	{
	case CreatureState::Moving:
		UpdateMoveState(attackables);
		break;
	case CreatureState::UpdateAttackingState:
		UpdateAttackingState(attackables);
		break;
	case CreatureState::UpdateAttackCooldownState:
		UpdateAttackCooldownState(attackables);
		break;
	default:
		assert(false && "Invalid CreatureState");
	}
}

void GameCore::TrashEnemy::Draw()
{
	BasicParam().GetMovingAnimation().Draw(GetPosition(), BasicParam().GetSpriteSize());
	DrawDebug();
}

void GameCore::TrashEnemy::TakeOnAttack(int takeAttackPower)
{
	OnDamage(takeAttackPower);
	if(CheckOnDeath())
	{
		m_removeSceneTrashEnemy(*this);
	}
}
