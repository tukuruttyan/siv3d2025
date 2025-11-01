#include "stdafx.h"
#include "DeepSeaFish.h"

GameCore::DeepSeaFish::DeepSeaFish(CreatureBasicParam basicParam, s3d::Vec2 position, const std::function<void(DeepSeaFish&)> removeSceneFish)
	: CreatureBase(basicParam, position),
	  m_removeSceneFish(removeSceneFish)
{
}

void GameCore::DeepSeaFish::Update(const std::vector<ITakableSeaFishAttack*>& attackables)
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

void GameCore::DeepSeaFish::Draw()
{
	BasicParam().GetMovingAnimation().Draw(GetPosition(), BasicParam().GetSpriteSize());
	DrawDebug();
}

void GameCore::DeepSeaFish::TakeOnAttack(int takeAttackPower)
{
	OnDamage(takeAttackPower);
	if (CheckOnDeath())
	{
		m_removeSceneFish(*this);
	}
}
