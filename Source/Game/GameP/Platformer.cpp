#include "Platformer.h"

#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "Framework/Framework.h"
#include "Enemy.h"

#include <array>



bool Platformer::Initialize()
{
	


	//Audio
	cg::g_audioSystem.AddAudio("hit", "Audio/boom.wav");
	cg::g_audioSystem.AddAudio("coin", "Audio/coin.wav");
	
	//Scene
	m_scene = std::make_unique<cg::Scene>();
	m_scene->Load("Scenes/tilemap.json");
	m_scene->Load("Scenes/Platformer.json");
	m_scene->Initialize();

	//Events
	cg::EventManager::Instance().Subscribe("AddPoints", this, std::bind(&Platformer::OnAddPoints, this, std::placeholders::_1));
	cg::EventManager::Instance().Subscribe("PlayerDie", this, std::bind(&Platformer::OnPlayerDead, this, std::placeholders::_1));

	return true;
}

void Platformer::Shutdown()
{
}

void Platformer::Update(float dt)
{

	switch (m_state)
	{
		//Title Screen
	case eState::Title:
	{	
		m_scene->GetActorByName("Death")->active = false;
		m_state = eState::Game;
		/*auto actor = INSTANTIATE(Actor, "Crate");
		actor->transform.position = { cg::random(0, cg::g_renderer.getWidth()), 100 };
		actor->Initialize();
		m_scene->Add(std::move(actor));*/

	}
		//if (cg::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE)) {
		//	m_scene->GetActorByName("Title")->active = true;
		//	m_state = eState::StartGame;
		//}
		break;


		//Start Game
	case eState::StartGame:
	{
		//auto bat = INSTANTIATE(Enemy, "Enemy");
		//bat->transform.position = { cg::random(0, cg::g_renderer.getWidth()), -100 };
		//bat->Initialize();
		////bat->m_physicsComponent = bat->GetComponent<cg::PhysicsComponent>();
		//m_scene->Add(std::move(bat));
		m_state = eState::StartLevel;
	}
		break;


		//Reset and Start Level
	case eState::StartLevel: {
		//m_scene->RemoveAll();
		m_state = eState::Game;
		break;
	}


						   //Game Running
	case eState::Game:
		if (m_spawnTime <= 0) {
			auto coin = INSTANTIATE(Actor, "Coin");
			coin->transform.position = { cg::random(0, cg::g_renderer.getWidth()), -100 };
			coin->Initialize();
			m_scene->Add(std::move(coin));
			m_spawnTime = m_spawnRate;
		}
		else m_spawnTime -= dt;
		break;


		//Player Just Died
	case eState::PlayerDeadStart:
		m_state = eState::PlayerDead;
		break;


		//Player Waiting for Restart
	case eState::PlayerDead:

		break;


		//Game Over
	case eState::GameOverStart:
	{
		m_state = eState::GameOver;
	}
	break;


	//Over
	case eState::GameOver:
		break;
	default:
		break;
	}
	m_scene->Update(dt);
}

void Platformer::Draw(cg::Renderer& renderer)
{
	m_scene->Draw(renderer);
}

void Platformer::OnAddPoints(const cg::Event& event)
{
	m_score += std::get<int>(event.data);
	m_scene->GetActorByName("CoinCount")->GetComponent<cg::TextRenderComponent>()->SetText("Coins " + std::to_string(m_score));
	cg::g_audioSystem.PlayOneShot("coin", false);
	if (m_score % 50 == 0) {
		m_scene->GetActor<cg::Enemy>()->speed *= 1.4;
	}
	
}

void Platformer::OnPlayerDead(const cg::Event& event)
{
	m_state = eState::PlayerDead;
	m_scene->GetActorByName("Death")->active = true;
	cg::g_audioSystem.PlayOneShot("hit", false);
	
}
