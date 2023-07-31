#pragma once
#include <memory>

namespace cg
{
	class Game
	{
		//class Renderer;
		//class Scene;
	public:
		Game() {}
		virtual ~Game() = default;
		virtual bool Initialize() = 0;
		virtual void Shutdown() = 0;

		virtual void Update(float dt) = 0;
		virtual void Draw(class Renderer& renderer) = 0;

		int GetScore() const { return m_score; }
		void AddPoints(int points) { m_score += points; }

		int GetLives() const { return m_lives; }
		void SetLives(int lives) { m_lives = lives; }
		std::unique_ptr<class Scene> m_scene;

	protected:
		int m_score = 0;
		int m_lives = 0;
	};
}