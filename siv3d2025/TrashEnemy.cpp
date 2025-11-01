#include "stdafx.h"
#include "TrashEnemy.h"
#include <exception>

GameCore::TrashEnemy::TrashEnemy(CreatureBasicParam basicParam, TrashEnemyAnimation animation, s3d::Vec2 position, const std::function<void(TrashEnemy&)> removeSceneTrashEnemy)
	: CreatureBase(basicParam, position),
	  m_animation(animation),
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
	m_animation.DrawMove(GetPosition());
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
