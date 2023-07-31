#pragma once
#include "Framework/Actor.h"
class Laser : public cg::Actor
{
public:
	Laser(const cg::Transform& transform, std::shared_ptr<cg::Model> model) :
		Actor{ transform, model }
	{}
	void Update(float dt) override;
	void OnCollision(Actor* other) override;
private:
	float m_updateRate = 2.0f;
};