#pragma once
#include "SceneBase.h"

namespace GameCore
{
	class StageA final : public SceneBase
	{
	public:
		StageA(SceneBaseContext context);

	private:
		void OnEnter() override;
		void Update () override;
		void OnExit () override;
	};
}
