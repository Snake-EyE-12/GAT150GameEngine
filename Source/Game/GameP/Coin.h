#pragma once
#include "Framework/Actor.h"
#include "Framework/Components/PhysicsComponent.h"



namespace cg
{
	class Coin : public Actor
	{
	public:
		CLASS_DECLARATION(Coin);

		bool Initialize() override;
		void Update(float dt) override;


	};
}
