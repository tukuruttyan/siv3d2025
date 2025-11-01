#include "stdafx.h"
#include "DeepSeaFish.h"

GameCore::DeepSeaFish::DeepSeaFish(const std::vector<Kirimi>& kirimis, s3d::Vec2 position, const std::function<void(DeepSeaFish&)> removeSceneFish)
	: CreatureBase(CombineKirimiParam(kirimis), position),
	  m_kirimis(kirimis),
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
	for (auto& kirimi : m_kirimis)
	{
		kirimi.Draw(GetPosition());
	}
	/*BasicParam().GetMovingAnimation().Draw(GetPosition(), BasicParam().GetSpriteSize());*/
	DrawDebug();
}

GameCore::CreatureBasicParam GameCore::DeepSeaFish::CombineKirimiParam(const std::vector<Kirimi>& kirimis)
{
	CreatureBasicParam result = kirimis.front().GetParam();

	for (size_t i = 1; i < kirimis.size(); ++i)
	{
		result = result + kirimis[i].GetParam();
	}

	return result;
}

void GameCore::DeepSeaFish::TakeOnAttack(int takeAttackPower)
{
	OnDamage(takeAttackPower);
	if (CheckOnDeath())
	{
		m_removeSceneFish(*this);
	}
}
