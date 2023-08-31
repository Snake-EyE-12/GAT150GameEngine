#include "Player.h"
#include "Framework/Components/PhysicsComponent.h"
#include "Framework/Components/SpriteAnimRenderComponent.h"

#include "Input/InputSystem.h"
#include "Framework/Event/EventManager.h"


namespace cg
{
	CLASS_DEFINITION(Player);
	bool Player::Initialize()
	{
		Actor::Initialize();
		m_physicsComponent = GetComponent<cg::PhysicsComponent>();
		m_sarc = GetComponent<cg::SpriteAnimRenderComponent>();
		
		return true;
	}


	void Player::Update(float dt)
	{
		Actor::Update(dt);

		if (dead) return;
		//Checks
		Vector2 velocity = m_physicsComponent->m_velocity;
		bool onGround = (groundCount > 0);

		//Player Input
		float dir = 0;
		if (cg::g_inputSystem.GetKeyDown(SDL_SCANCODE_A)) dir = -1;
		if (cg::g_inputSystem.GetKeyDown(SDL_SCANCODE_D)) dir = 1;

		
		cg::Vector2 forward = cg::Vector2{ 1, 0 };
		m_physicsComponent->ApplyForce(forward * speed * dir * ((onGround) ? 1 : 0.5));

		//Player Jump
		if (onGround && cg::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) && !cg::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE)) {
			
			cg::Vector2 up = cg::Vector2{m_physicsComponent->m_velocity.x, -1.0f};
			m_physicsComponent->SetVelocity(up * jump);
		}
		//Animation
		if (std::fabs(velocity.y) > 1.0f) {
			m_sarc->SetSequence("jump");
		}
		else if (std::fabs(velocity.x) > 0.2f) {
			if(dir != 0 ) m_sarc->flipH = dir < 0;
			m_sarc->SetSequence("run");
		}
		else m_sarc->SetSequence("idle");


	}

	void Player::OnCollisionEnter(Actor* other) {
		if (other->tag == "Ground") groundCount++;
		if (other->tag == "Enemy") {
			m_sarc->SetSequence("dead");
			dead = true;
			EventManager::Instance().DispatchEvent("PlayerDie", 1);
		}
		if (other->tag == "coin") {
			EventManager::Instance().DispatchEvent("AddPoints", 10);
			other->m_destroyed = true;
		}
	}
	void Player::OnCollisionExit(Actor* other) {
		if (other->tag == "Ground") groundCount--;
	}



	void Player::Read(const json_t& value) {
		Actor::Read(value);
		READ_DATA(value, speed);
		READ_DATA(value, jump);
	}
}