#pragma once
#include "Core/Core.h"
#include "Renderer/Model.h"
#include <memory>
#include "Components/Component.h"

namespace cg
{
	class Actor
	{
	public:
		Actor() = default;
		Actor(const cg::Transform& transform) :
			m_transform{ transform }
		{}

		virtual void Update(float dt);
		virtual void Draw(cg::Renderer& renderer);

		void AddComponent(std::unique_ptr<Component> component);

		template<typename T>
		T* GetComponent();

		float GetRadius() { return 15.0f; }

		virtual void OnCollision(Actor* other) {}


		class Scene* m_scene = nullptr;
		friend class Scene;
		class Game* m_game = nullptr;
		cg::Transform m_transform;
		std::string m_tag;
		float m_lifespan = -1.0f;

	protected:
		std::vector<std::unique_ptr<Component>> m_components;

		bool m_destroyed = false;

	};
	template<typename T>
	inline T* Actor::GetComponent()
	{
		for (auto& component : m_components) {
			T* result = dynamic_cast<T*>(component.get());
			if (result) return result;
		}
		return nullptr;
	}
}