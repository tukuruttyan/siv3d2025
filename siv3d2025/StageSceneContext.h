#pragma once
#include <Siv3D.hpp>
#include <memory>
#include "TrashFactory.h"
#include "KirimiParams.h"

namespace GameCore
{
	enum GameState
	{
		Playing,
		GameClear,
		GameOver
	};

	struct StageSceneContext final
	{
	public:
		StageSceneContext(std::shared_ptr<const TrashFactory> trashFactory, float sceneHeight);
		void Update();
		void GameOver();
		void GameClear();
		void Reset();

		TrashFactory& getTrashFactory() const;
		void MinusResource(int minus)
		{
			m_resource -= minus;
		}
		float  getSceneHeight() const;
		double getScrollSpeed() const;
		GameState State() const { return  m_gameState; }
		double Resource() const { return m_resource; }
		const std::array<std::pair<const SpriteAnimation, const CreatureBasicParam>, 8>& getKirimiInventory() const;
		StageSceneContext& operator=(const StageSceneContext& other);
	private:
		std::shared_ptr<const TrashFactory> m_trashFactory;
		const float m_sceneHeight;
		const double m_scrollSpeed = 300.0;
		const
		std::array<std::pair<const SpriteAnimation, const CreatureBasicParam>, 8> m_kirimiInventory{
		std::make_pair(GameCore::EnemyParams::KirimiAnims()[static_cast<std::size_t>(GameCore::EnemyParams::KirimiType::FishEye)],      GameCore::EnemyParams::KirimiParams()[static_cast<std::size_t>(GameCore::EnemyParams::KirimiType::FishEye)]),
		std::make_pair(GameCore::EnemyParams::KirimiAnims()[static_cast<std::size_t>(GameCore::EnemyParams::KirimiType::SharpFin)],     GameCore::EnemyParams::KirimiParams()[static_cast<std::size_t>(GameCore::EnemyParams::KirimiType::SharpFin)]),
		std::make_pair(GameCore::EnemyParams::KirimiAnims()[static_cast<std::size_t>(GameCore::EnemyParams::KirimiType::FlatFin)],      GameCore::EnemyParams::KirimiParams()[static_cast<std::size_t>(GameCore::EnemyParams::KirimiType::FlatFin)]),
		std::make_pair(GameCore::EnemyParams::KirimiAnims()[static_cast<std::size_t>(GameCore::EnemyParams::KirimiType::SquareBody)],   GameCore::EnemyParams::KirimiParams()[static_cast<std::size_t>(GameCore::EnemyParams::KirimiType::SquareBody)]),
		std::make_pair(GameCore::EnemyParams::KirimiAnims()[static_cast<std::size_t>(GameCore::EnemyParams::KirimiType::TryangleBody)], GameCore::EnemyParams::KirimiParams()[static_cast<std::size_t>(GameCore::EnemyParams::KirimiType::TryangleBody)]),
		std::make_pair(GameCore::EnemyParams::KirimiAnims()[static_cast<std::size_t>(GameCore::EnemyParams::KirimiType::ThornMouth)],   GameCore::EnemyParams::KirimiParams()[static_cast<std::size_t>(GameCore::EnemyParams::KirimiType::ThornMouth)]),
		std::make_pair(GameCore::EnemyParams::KirimiAnims()[static_cast<std::size_t>(GameCore::EnemyParams::KirimiType::Empty)],        GameCore::EnemyParams::KirimiParams()[static_cast<std::size_t>(GameCore::EnemyParams::KirimiType::Empty)]),
		std::make_pair(GameCore::EnemyParams::KirimiAnims()[static_cast<std::size_t>(GameCore::EnemyParams::KirimiType::Empty)],        GameCore::EnemyParams::KirimiParams()[static_cast<std::size_t>(GameCore::EnemyParams::KirimiType::Empty)]),
		};

		double m_startResources = 1000.0f;
		const double m_resourcesPerSecond = 5;
		double m_resource = 1000.0f;
		GameState m_gameState = Playing;
	};
}
