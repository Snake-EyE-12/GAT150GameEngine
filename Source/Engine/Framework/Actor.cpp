#include "Actor.h"
#include "Components/RenderComponent.h"
#include "Components/PhysicsComponent.h"

namespace cg
{
	CLASS_DEFINITION(Actor);

	bool Actor::Initialize()
	{
		for (auto& component : components) {
			component->Initialize();
		}
		return true;
	}
	void Actor::OnDestroy()
	{
		for (auto& component : components) {
			component->OnDestroy();
		}
	}
	void Actor::Update(float dt) {
		if (lifespan != -1.0f) {
			lifespan -= dt;
			if (lifespan <= 0) {
				m_destroyed = true;
			}
		}
		for (auto& component : components) {
			component->Update(dt);
		}
		
	}
	void Actor::Draw(cg::Renderer& renderer) {

		for (auto& component : components) {
			RenderComponent* rComp = dynamic_cast<RenderComponent*>(component.get());
			if (rComp) {
				rComp->Draw(renderer);
			}
		}
	}
	void Actor::AddComponent(std::unique_ptr<Component> component)
	{
		component->m_owner = this;
		components.push_back(std::move(component));
	}
	void Actor::Read(const rapidjson::Value& value) {
		Object::Read(value);

		READ_DATA(value, tag);
		READ_DATA(value, lifespan);

		if(HAS_DATA(value, transform)) transform.Read(value);

		if (HAS_DATA(value, components) && GET_DATA(value, components).IsArray()) {
			for (auto& componentValue : GET_DATA(value, components).GetArray()) {
				std::string type;
				READ_DATA(componentValue, type);
				auto component = CREATE_CLASS(Component, type);

				component->Read(componentValue);
				AddComponent(std::move(component));
			}
		}
	}
}
