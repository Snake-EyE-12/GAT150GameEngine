#pragma once
#include "Object.h"
#include "Core/Core.h"
#include "Renderer/Model.h"
#include <memory>
#include "Components/Component.h"

namespace cg
{
	class Actor : public Object
	{
	public:
		Actor() = default;
		Actor(const cg::Transform& transform) :
			transform{ transform }
		{}

		CLASS_DECLARATION(Actor);

		virtual bool Initialize() override;
		virtual void OnDestroy() override;

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
		cg::Transform transform;
		std::string tag;
		float lifespan = -1.0f;

	protected:
		std::vector<std::unique_ptr<Component>> components;

		bool m_destroyed = false;

	};
	template<typename T>
	inline T* Actor::GetComponent()
	{
		for (auto& component : components) {
			T* result = dynamic_cast<T*>(component.get());
			if (result) return result;
		}
		return nullptr;
	}
}