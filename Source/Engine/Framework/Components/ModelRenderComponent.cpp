#include "ModelRenderComponent.h"
#include "Framework/Actor.h"
#include "Framework/Resource/ResourceManager.h"
namespace cg
{
	CLASS_DEFINITION(ModelRendererComponent);
	bool ModelRendererComponent::Initialize()
	{
		m_model = GET_RESOURCE(Model, modelName);
		return true;
	}
	void ModelRendererComponent::Update(float dt)
	{
	}

	void ModelRendererComponent::Draw(Renderer& renderer)
	{
		m_model->Draw(renderer, m_owner->transform);
	}
	void ModelRendererComponent::Read(const json_t& value)
	{
		READ_DATA(value, modelName);
	}
}
