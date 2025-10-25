#include "stdafx.h"
#include "SpawnCooldown.h"

namespace GameCore
{
	SpawnCooldown::SpawnCooldown(float cooldownDuration_secs, float cooldownDuring_secs)
		: m_cooldownDuration_secs(cooldownDuration_secs)
		, m_cooldownDuring_secs(cooldownDuring_secs)
	{
	}

	SpawnCooldown SpawnCooldown::WithTick(float deltaTime_secs) const
	{
		return SpawnCooldown{
			m_cooldownDuration_secs,
			m_cooldownDuring_secs + deltaTime_secs
		};
	}

	SpawnCooldown SpawnCooldown::WithCheckCount(bool& didCount) const
	{
		if (m_cooldownDuring_secs >= m_cooldownDuration_secs)
		{
			didCount = true;
			return SpawnCooldown{ m_cooldownDuration_secs, 0.0f };
		}
		else
		{
			didCount = false;
			return *this;
		}
	}
}
