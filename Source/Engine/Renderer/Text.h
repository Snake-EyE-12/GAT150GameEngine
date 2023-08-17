#pragma once
#include "Font.h"
#include "Core/Math/Color.h"
#include <string>
#include <memory>
#include "Framework/Resource/Resource.h"

struct SDL_Texture;

namespace cg
{
	class Renderer;
	class Text : public Resource
	{
	public:
		Text() = default;
		Text(std::shared_ptr<Font> font) : m_font{ font } { }
		~Text();
		virtual bool Create(std::string filename, ...) override;
		bool Load(Renderer& renderer, const std::string& text, const Color& color);
		void Draw(Renderer& renderer, int x, int y);

	private:
		std::shared_ptr<Font> m_font;
		SDL_Texture* m_texture = nullptr;
	};
}