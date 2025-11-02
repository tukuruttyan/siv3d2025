#pragma once
#include <Siv3D.hpp>
#include "DamageEffect.h"
#include "DamageBubbleEffect.h"

class EffectManager
{
public:
	// --- シングルトンアクセス ---
	static EffectManager& Instance()
	{
		static EffectManager instance;
		return instance;
	}

	// コピー禁止・ムーブ禁止
	EffectManager(const EffectManager&) = delete;
	EffectManager& operator=(const EffectManager&) = delete;
	EffectManager(EffectManager&&) = delete;
	EffectManager& operator=(EffectManager&&) = delete;

	// --- 更新＆描画 ---
	void Update()
	{
		m_effect.update();
	}

	void Draw() const
	{
		// Effect は update() 内で描画されるが、
		// 明示的に描画順を調整したい場合にここで描いてもよい。
	}

	// --- エフェクト生成 ---
	void AddDamageEffect(const Vec2& pos)
	{
		m_effect.add<DamageEffect>(pos);
	}
	void AddDamageBubbleEffect(const Vec2& pos)
	{
		m_effect.add<DamageBubbleEffect>(pos);
	}

	template <class T, class... Args>
	void Add(Args&&... args)
	{
		m_effect.add<T>(std::forward<Args>(args)...);
	}

private:
	// コンストラクタをprivateにして外部生成を禁止
	EffectManager() = default;
	~EffectManager() = default;

	Effect m_effect;
};
