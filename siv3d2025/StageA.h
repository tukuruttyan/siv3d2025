#pragma once
#include "SceneBase.h"

namespace GameCore
{
	class StageA final : public SceneBase
	{
	private:
		void OnEnter() override;
		void Update () override;
		void OnExit () override;


	};
}
