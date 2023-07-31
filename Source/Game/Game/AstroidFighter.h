#pragma once
#include "Framework/Game.h"
#include "Renderer/Text.h"

class AstroidFighter : public cg::Game
{
public:
	enum eState
	{
		Title,
		StartGame,
		StartLevel,
		Game,
		PlayerDeadStart,
		PlayerDead,
		GameOverStart,
		GameOver
	};

public:
	virtual bool Initialize() override;

	virtual void Shutdown() override;

	virtual void Update(float dt) override;

	virtual void Draw(cg::Renderer& renderer) override;
	void SetState(eState state) { m_state = state; }
	bool AttemptClearTetris();
	void TetrisMaxHeightReached();

private:
	eState m_state = eState::Title;
	float m_spawnTime = 0.0f;
	float m_spawnRate = 3.0f;
	float m_stateTimer = 1.0f;

	std::shared_ptr<cg::Font> m_fontBig;
	std::shared_ptr<cg::Font> m_fontMedium;
	std::shared_ptr<cg::Font> m_fontSmall;
	std::unique_ptr<cg::Text> m_scoreText;
	std::unique_ptr<cg::Text> m_livesText;
	std::unique_ptr<cg::Text> m_titleText;
	std::unique_ptr<cg::Text> m_controlsText;
	std::unique_ptr<cg::Text> m_gameOverText;


};
