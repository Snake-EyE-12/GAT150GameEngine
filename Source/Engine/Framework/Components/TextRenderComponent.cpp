#include "TextRenderComponent.h"
#include "Framework/Actor.h"
#include "Framework/Resource/ResourceManager.h"

#include <memory>

namespace cg
{
	CLASS_DEFINITION(TextRenderComponent)
	TextRenderComponent::TextRenderComponent(const TextRenderComponent& other)
	{
		text = other.text;
		fontName = other.fontName;
		fontSize = other.fontSize;
		m_changed = true;
		m_text = std::make_unique<Text>(*other.m_text.get());
	}
	bool TextRenderComponent::Initialize()
	{
		if (!fontName.empty()) {
			m_text = std::make_unique<cg::Text>(GET_RESOURCE(cg::Font, fontName, fontSize));
			return true;
		}
	}
	void TextRenderComponent::Update(float dt)
	{
	}
	void TextRenderComponent::Draw(Renderer& renderer)
	{
		// update the text if changed
		if (m_changed)
		{
			m_changed = false;
			// create text using text string and color
			m_text->Create(renderer, text, { 1, 1, 1, 1 });
		}
		// draw text
		m_text->Draw(renderer, m_owner->transform);
	}
	void TextRenderComponent::SetText(const std::string& string)
	{
		// check if text has changed, if changed set new string and update
		if (string != text)
		{
			text = string;
			m_changed = true;
		}
	}

	void TextRenderComponent::Read(const rapidjson::Value& value)
	{
		READ_DATA(value, text);
		READ_DATA(value, fontName);
		READ_DATA(value, fontSize);
	}
}