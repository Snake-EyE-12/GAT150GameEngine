#include "Laser.h"

void Laser::Update(float dt)
{
	Actor::Update(dt);
	m_updateRate -= dt;
	if (m_updateRate <= 0) {
		m_transform.scale *= -1;
		m_updateRate += 0.3f;
	}
}

void Laser::OnCollision(Actor* other)
{
}
