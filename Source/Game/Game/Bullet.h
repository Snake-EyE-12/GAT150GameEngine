#pragma once
#include "Framework/Actor.h"
class Bullet : public cg::Actor
{
public:
	Bullet(float speed, const cg::Transform& transform) :
		Actor{ transform },
		m_speed{ speed }
	{
		lifespan = 2.0f;
	}
	void Update(float dt) override;
	void OnCollision(Actor* other) override;
private:
	float m_speed = 0;
};