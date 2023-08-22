#pragma once
#include "Framework/Actor.h"
#include "Core/Math/Vector2.h"

namespace cg
{
	class Block : public cg::Actor
	{
	//CLASS_DEFINITION(Block);
	public:
		Block(float speed, const cg::Transform& transform, int type, cg::Vector2 forwardAngle) :
			//Actor{ transform, GetModel(type)},
			Actor{ transform },
			m_speed{ speed },
			m_forwardV{ forwardAngle }
		{

		}
		void Update(float dt) override;
		void OnCollision(Actor* other) override;
		void Place();
		bool Destroy();
		std::shared_ptr<cg::Model> GetModel(int value) {
			/*switch (value)
			{
			case 0 :
			{
				return cg::g_manager.Get("block0.txt");
			}
			case 1:
			{
				return cg::g_manager.Get("block1.txt");
			}
			case 2:
			{
				return cg::g_manager.Get("block2.txt");
			}
			case 3:
			{
				return cg::g_manager.Get("block3.txt");
			}
			case 4:
			{
				return cg::g_manager.Get("block4.txt");
			}
			case 5:
			{
				return cg::g_manager.Get("block5.txt");
			}
			default:
			{
				return cg::g_manager.Get("block6.txt");
			}

			}*/
		}
		bool m_placed = false;
	private:
		float m_speed = 0;
		cg::Vector2 m_forwardV;
		float m_gravity = 10;

	};
}