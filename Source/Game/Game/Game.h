#pragma once
#include <memory>

namespace kiko
{
	class Scene;

	class Game
	{
	public:
		Game() = default;
		virtual ~Game() = default;

		virtual bool Initalize() = 0;
		virtual void Shutdown() = 0;
		
		virtual void Update(float dt) = 0;
		virtual void Draw(class Renderer& renderer) = 0;

		int GetScore() const { return m_score; }
		int AddPoints(int points) 
		{ 
			return m_score += points;
		}

		int GetLives() const { return m_lives; }
		void SetLives(int lives) { m_lives = lives; }


	protected:
		std::unique_ptr<Scene> m_scene = nullptr;

		int m_score = 0;
		int m_lives = 0;
	};
}