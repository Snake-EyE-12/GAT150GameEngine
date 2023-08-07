#include "Actor.h"
#include "Components/RenderComponent.h"
#include "Components/PhysicsComponent.h"

namespace cg
{
	void Actor::Update(float dt) {
		if (m_lifespan != -1.0f) {
			m_lifespan -= dt;
			if (m_lifespan <= 0) {
				m_destroyed = true;
			}
		}
		for (auto& component : m_components) {
			PhysicsComponent* rComp = dynamic_cast<PhysicsComponent*>(component.get());
			if (rComp) {
				rComp->Update(dt);
			}
		}
		
	}
	void Actor::Draw(cg::Renderer& renderer) {

		for (auto& component : m_components) {
			RenderComponent* rComp = dynamic_cast<RenderComponent*>(component.get());
			if (rComp) {
				rComp->Draw(renderer);
			}
		}
	}
	void Actor::AddComponent(std::unique_ptr<Component> component)
	{
		component->m_owner = this;
		m_components.push_back(std::move(component));
	}
}
