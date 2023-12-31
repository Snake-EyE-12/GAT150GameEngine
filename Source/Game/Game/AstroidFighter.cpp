#include "AstroidFighter.h"
#include "Player.h"
#include "Enemy.h"

#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"

#include "Renderer/Renderer.h"

#include "Framework/Framework.h"

#include <array>



bool AstroidFighter::Initialize()
{
	//UI
	//m_font = cg::ResourceManager::Instance().Get<cg::Font>("Marlboro.ttf", 34);


	/*m_fontSmall = std::make_shared<cg::Font>("Marlboro.ttf", 24);
	m_fontMedium = std::make_shared<cg::Font>("Marlboro.ttf", 50);
	m_fontBig = std::make_shared<cg::Font>("Marlboro.ttf", 100);*/


	//m_scoreText = std::make_unique<cg::Text>(m_fontSmall);
	//m_livesText = std::make_unique<cg::Text>(m_fontSmall);
	//m_scoreText->Create(cg::g_renderer, "Score:", cg::Color{ 1, 1, 1, 1 });
	//std::unique_ptr<cg::Text> mytext = std::make_unique<cg::Text>();
	//mytext->Create(cg::g_renderer, "Bob", cg::Color{ 1, 1, 1, 1 });
	//mytext->Draw(cg::g_renderer);
	//m_titleText = GET_RESOURCE(cg::Text, "Asteroid Fighter", cg::Color{ 1, 1, 1, 1 }, GET_RESOURCE(cg::Font, "Marlboro.ttf", 34));
	//m_titleText = std::make_unique<cg::Text>(m_fontBig);
	//m_titleText->Create(cg::g_renderer, "Asteroid Fighter", cg::Color{ 1, 1, 1, 1 });

	//m_controlsText = std::make_unique<cg::Text>(m_fontMedium);
	//m_controlsText->Create(cg::g_renderer, "Press Space To Play", cg::Color{ 0.6f, 0.6f, 0.5f, 1 });

	//m_gameOverText = std::make_unique<cg::Text>(m_fontBig);
	//m_gameOverText->Create(cg::g_renderer, "Game Over", cg::Color{ 1, 0, 0, 1 });





	//Audio
	cg::g_audioSystem.AddAudio("hit", "boom.wav");
	cg::g_audioSystem.AddAudio("zap", "zap.wav");
	cg::g_audioSystem.AddAudio("damage", "damage.wav");
	cg::g_audioSystem.AddAudio("lose", "lose.wav");
	cg::g_audioSystem.AddAudio("tetris", "tetrisQuiet.mp3");
	cg::g_audioSystem.AddAudio("line", "line.wav");

	//Scene
	m_scene = std::make_unique<cg::Scene>();
	m_scene->Load("scenes/SpaceScene.json");
	m_scene->Initialize();
	
	//Events
	cg::EventManager::Instance().Subscribe("AddPoints", this, std::bind(&AstroidFighter::OnAddPoints, this, std::placeholders::_1));
	cg::EventManager::Instance().Subscribe("PlayerDie", this, std::bind(&AstroidFighter::OnPlayerDead, this, std::placeholders::_1));

	return true;
}

void AstroidFighter::Shutdown()
{
}

void AstroidFighter::Update(float dt)
{
	
	switch (m_state)
	{
		//Title Screen
	case eState::Title:
		if (cg::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE)) {
			m_state = eState::StartGame;
			m_scene->GetActorByName("Background")->active = false;
		}
		break;


		//Start Game
	case eState::StartGame:
		m_score = 0;
		m_lives = 3;
		m_state = eState::StartLevel;
		cg::g_audioSystem.PlayOneShot("tetris", true);
		break;


		//Reset and Start Level
	case eState::StartLevel: {
		m_scene->RemoveAll();

		auto player = INSTANTIATE(Player, "Player");
		player->transform = cg::Transform{ { 400, 300 }, 0, 1 };
		player->Initialize();
		m_scene->Add(std::move(player));

		m_state = eState::Game;
		break;	
	}


		//Game Running
	case eState::Game:
		m_spawnTime += dt;
		if (m_spawnTime >= m_spawnRate) {
			auto enemy = INSTANTIATE(Enemy, "Enemy");
			enemy->transform = cg::Transform{ { cg::random(800), cg::random(600) }, cg::randomf(cg::TwoPi), 1 };
			enemy->Initialize();
			m_scene->Add(std::move(enemy));
			m_spawnTime = 0;
		}
		
		break;


		//Player Just Died
	case eState::PlayerDeadStart:
		m_stateTimer = 3;
		m_lives--;
		if (m_lives <= 0) m_state = eState::GameOverStart;
		else m_state = eState::PlayerDead;
		break;


		//Player Waiting for Restart
	case eState::PlayerDead:
		//Wait for seconds
		m_stateTimer -= dt;
		if (m_stateTimer <= 0) {
			m_state = eState::StartLevel;
		}
		break;


		//Game Over
	case eState::GameOverStart:
	{
		cg::g_audioSystem.PlayOneShot("lose", false);
		m_stateTimer = 3;
		//Player* plr = m_scene->GetActor<Player>();
		//if (plr) plr->Destroy();
		m_state = eState::GameOver;
	}
		break;


		//Over
	case eState::GameOver:
		m_stateTimer -= dt;
		if (m_stateTimer <= 0) {
			m_state = eState::Title;
		}
		break;
	default:
		break;
	}
	
	//m_scoreText->Create(cg::g_renderer, std::to_string(m_score), { 0.6f, 0.6f, 0.5f, 1 });
	//m_livesText->Create(cg::g_renderer, std::to_string(m_lives), { 0.94f, 0.3f, 0.3f, 1 });
	m_scene->Update(dt);
}

void AstroidFighter::Draw(cg::Renderer& renderer)
{
	
	if (m_state == eState::Title) {
		//m_titleText->Draw(renderer, 150, 200);
		//m_controlsText->Draw(renderer, 200, 300);
		//GET_RESOURCE()
	}
	else {
		//m_livesText->Draw(renderer, 760, 40);

	}
	//m_scoreText->Draw(renderer, 40, 40);
	//if (m_state == eState::GameOver) m_gameOverText->Draw(renderer, 250, 230);
	

	m_scene->Draw(renderer);
}

void AstroidFighter::OnAddPoints(const cg::Event& event)
{
	m_score += std::get<int>(event.data);
}

void AstroidFighter::OnPlayerDead(const cg::Event& event)
{
	m_state = eState::PlayerDeadStart;
}

bool AstroidFighter::AttemptClearTetris()
{
	if (m_state != eState::Game) return false;
	const int width = 10;
	const int height = 10;
	int eachBlockLine[width][height];
	//for (Block* block : m_scene->GetBlocks()) {
	//	eachBlockLine[(int)(cg::Clamp(block->transform.position.x / cg::g_renderer.getWidth(), 0.0f, 0.99f) * width)][(int)(cg::Clamp(block->transform.position.y / cg::g_renderer.getHeight(), 0.0f, 0.99f) * height)] = 1;
	//}
	int tetris = -1;

	for (int y = 0; y < height; y++) {
		bool lineFull = true;
		for (int x = 0; x < width; x++) {
			if (eachBlockLine[x][y] != 1) {
				lineFull = false;
				break;
			}
		}
		if (lineFull) {
			//std::cout << "Found full Line at: Y: " << y << std::endl;
			tetris = y;
		}
	}
	if (tetris == -1) return false;
	//for (Block* block : m_scene->GetBlocks()) {
	//	if ((int)(cg::Clamp(block->transform.position.y / cg::g_renderer.getHeight(), 0.0f, 0.99f) * height) == tetris) {
	//		block->Destroy();
	//	}
	//}
	cg::g_audioSystem.PlayOneShot("line", false);
	return true;


}

void AstroidFighter::TetrisMaxHeightReached()
{
	m_state = eState::GameOverStart;
	/*for (Block* block : m_scene->GetBlocks()) {
		block->Destroy();
	}*/

}
