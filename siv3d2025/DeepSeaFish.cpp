#include "stdafx.h"
#include "DeepSeaFish.h"

GameCore::DeepSeaFish::DeepSeaFish(CreatureBasicParam basicParam, s3d::Vec2 position)
	: CreatureBase(basicParam, position) {
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
	GetBasicParam().GetMovingAnimation().Draw(GetPosition());
	DrawDebug();
}

void GameCore::DeepSeaFish::TakeOnAttack(int attackPower)
{
}
