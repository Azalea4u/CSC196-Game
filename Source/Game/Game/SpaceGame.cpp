#include "SpaceGame.h"
#include "Player.h"
#include "Enemy.h"

#include "FrameWork/Scene.h"

#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "Renderer/ModelManager.h"

bool SpaceGame::Initalize()
{
	// create text
	m_font = std::make_shared<kiko::Font>("ArcadeClassic.ttf", 24);
	m_scoreText = std::make_unique<kiko::Text>(m_font);
	m_scoreText->Create(kiko::g_renderer, "SCORE 0000", kiko::Color{ 1, 0, 1, 1 });

	m_titleText = std::make_unique<kiko::Text>(m_font);
	m_titleText->Create(kiko::g_renderer, "ASTEROIDs", kiko::Color{ 1, 0, 1, 1 });

	// load audio
	kiko::g_audioSystem.AddAudio("Laser", "Laser_Shoot.wav");

	m_scene = std::make_unique<kiko::Scene>();
	
	return false;
}

void SpaceGame::Shutdown()
{

}

void SpaceGame::Update(float dt)
{
	switch (m_state)
	{
		case SpaceGame::Title:
			if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE))
				m_state = StartGame;

			break;
		
		case SpaceGame::StartGame:
			m_score = 0;
			m_lives = 3;
			m_state = StartLevel;

			break;
        
		case SpaceGame::StartLevel:
		{
			m_scene->RemoveAll();

			//creates player
			std::unique_ptr<Player> player = std::make_unique<Player>(200.0f, kiko::Pi, kiko::Transform{ {400, 300 }, 0, 6}, kiko::g_modelManager.Get("Star_Shape.txt"));
			player->m_tag = "Player";
			player->m_game = this;
			m_scene->Add(std::move(player));
		}
			m_state = eState::Game;
			break;
		
		case SpaceGame::Game:
			m_SpawnTimer += dt;
			if (m_SpawnTimer >= m_SpawnTime)
			{
				m_SpawnTimer = 0;

				// creates enemy
				std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(kiko::randomf(75.0f, 150.f), kiko::Pi, kiko::Transform{ {kiko::random(800), kiko::random(600)}, 0, 6 }, kiko::g_modelManager.Get("Star_Shape.txt"));
				enemy->m_tag = "Enemy";
				m_scene->Add(std::move(enemy));
			}

			break;
		
		case SpaceGame::PlayerDead:
			if (m_lives == 0) m_state = eState::GameOver;
			else m_state = eState::StartLevel;

			break;
		
		case SpaceGame::GameOver:
			break;

		default:
			break;
	}

	m_scoreText->Create(kiko::g_renderer, "SCORE " + std::to_string(m_score), kiko::Color{ 1, 1, 1, 1 });
	m_scene->Update(dt);
}

void SpaceGame::Draw(kiko::Renderer& renderer)
{
	if (m_state == eState::Title)
	{
		m_titleText->Draw(renderer, 400, 300);
	}

	m_scoreText->Draw(renderer, 40, 40);
	m_scene->Draw(renderer);
}
