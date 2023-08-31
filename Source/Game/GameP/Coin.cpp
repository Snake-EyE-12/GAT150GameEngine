#include "Coin.h"
#include "Framework/Components/PhysicsComponent.h"
#include "Input/InputSystem.h"
#include "Player.h"
#include "Framework/Scene.h"


namespace cg
{
	CLASS_DEFINITION(Coin);
	bool Coin::Initialize()
	{
		Actor::Initialize();

		return true;
	}


	void Coin::Update(float dt)
	{
		Actor::Update(dt);


	}


	void Coin::Read(const json_t& value) {
		Actor::Read(value);
	}
}