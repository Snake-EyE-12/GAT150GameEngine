#pragma once
#include "Framework/Game.h"
#include "Framework/Scene.h"
#include "Renderer/Font.h"
#include "Framework/Event/EventManager.h"

class AstroidFighter : public cg::Game, cg::IEventListener
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
	void OnAddPoints(const cg::Event& event);
	void OnPlayerDead(const cg::Event& event);
	bool AttemptClearTetris();
	void TetrisMaxHeightReached();

private:
	eState m_state = eState::Title;
	float m_spawnTime = 0.0f;
	float m_spawnRate = 3.0f;
	float m_stateTimer = 1.0f;

	std::shared_ptr<cg::Font> m_font;


};
