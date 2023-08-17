#pragma once
#include "CollisionComponent.h"
namespace cg
{
	class CircleCollisionComponet : public CollisionComponent
	{
	public:
		CLASS_DECLARATION(CircleCollisionComponet);
		//bool Initialize() override;
		virtual void Update(float dt) override;
		virtual bool CheckCollision(CollisionComponent* collision) override;
		//void Read(const json_t& value);
	public:
		//std::string componentName
	};
}