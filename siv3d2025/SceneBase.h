#pragma once
#include "SceneBaseContext.h"

namespace GameCore
{
	class SceneBase
	{
	public:
		SceneBase(SceneBaseContext context);
		virtual ~SceneBase() = default;
		virtual void OnEnter() = 0;
		virtual void Update () = 0;
		virtual void OnExit () = 0;

	protected:
		//NOTE: 以下サンドボックスパターン
		template<typename T>
		void OnChangeScene()
		{
			m_context.OnChangeScene(typeid(T));
		}

	private:
		const SceneBaseContext m_context;
	};
}
