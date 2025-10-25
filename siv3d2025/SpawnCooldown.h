#pragma once

namespace GameCore
{
	struct SpawnCooldown final
	{
	public:
		explicit SpawnCooldown(float cooldownDuration_secs, float cooldownDuring_secs = 0.0f);

		SpawnCooldown WithTick(float deltaTime_secs) const;
		SpawnCooldown WithCheckCount(bool& didCount) const;

		float GetDuration() const { return m_cooldownDuration_secs; }
		float GetDuring() const { return m_cooldownDuring_secs; }

	private:
		float m_cooldownDuration_secs;
		float m_cooldownDuring_secs;
	};
}
