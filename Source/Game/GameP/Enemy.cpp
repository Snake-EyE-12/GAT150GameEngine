#include "Enemy.h"
#include "Framework/Components/PhysicsComponent.h"
#include "Input/InputSystem.h"
#include "Player.h"
#include "Framework/Scene.h"


namespace cg
{
	CLASS_DEFINITION(Enemy);
	bool Enemy::Initialize()
	{
		Actor::Initialize();
		m_physicsComponent = GetComponent<cg::PhysicsComponent>();

		return true;
	}


	void Enemy::Update(float dt)
	{
		Actor::Update(dt);

		cg::vec2 forward = cg::vec2{ 0, -1 }.Rotate(transform.rotation);
		Player* player = m_scene->GetActor<Player>();
		if (player)
		{
			cg::vec2 direction = player->transform.position - transform.position;
			if (m_physicsComponent) {
				m_physicsComponent->ApplyForce(direction.Normalized() * speed);

			}
			else {
				//m_physicsComponent = GetComponent<cg::PhysicsComponent>();
				//std::cout << "WTF" << std::endl;
			}
		}



	}

	void Enemy::OnCollisionEnter(Actor* other) {
	}
	void Enemy::OnCollisionExit(Actor* other) {
	}



	void Enemy::Read(const json_t& value) {
		Actor::Read(value);
		READ_DATA(value, speed);
	}
}