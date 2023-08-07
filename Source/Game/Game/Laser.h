#pragma once
#include "Framework/Actor.h"
class Laser : public cg::Actor
{
public:
	Laser(const cg::Transform& transform) :
		Actor{ transform }
	{}
	void Update(float dt) override;
	void OnCollision(Actor* other) override;
private:
	float m_updateRate = 2.0f;
};