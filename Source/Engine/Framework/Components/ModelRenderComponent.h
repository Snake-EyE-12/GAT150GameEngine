#pragma once
#include "RenderComponent.h"
#include "Renderer/Model.h"
namespace cg
{
	class ModelRendererComponent : public RenderComponent
	{
	public:
		CLASS_DECLARATION(ModelRendererComponent);

		bool Initialize() override;
		void Update(float dt) override;
		void Draw(class Renderer& renderer);

		virtual float GetRadius() override { return m_model->GetRadius(); }

	public:
		std::string modelName;
		res_t<Model> m_model;
	};
}