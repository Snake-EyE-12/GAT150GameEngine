#include "CircleCollisionComponent.h"
#include "Framework/Actor.h"
namespace cg
{
    CLASS_DEFINITION(CircleCollisionComponet);
    void CircleCollisionComponet::Update(float dt)
    {
    }

    bool CircleCollisionComponet::CheckCollision(CollisionComponent* collision)
    {
        float distance = m_owner->transform.position.Distance(collision->m_owner->transform.position);
        float radius = m_radius + collision->m_radius;
        return distance <= radius;

    }
    void CircleCollisionComponet::Read(const json_t& value) {

    }
}