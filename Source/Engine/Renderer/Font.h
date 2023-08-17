#pragma once
#include <string>
#include "Framework/Resource/Resource.h"


struct _TTF_Font;


namespace cg
{
	class Font : public Resource
	{
		friend class Text;
	public:
		Font() = default;
		Font(const std::string& filename, int fontSize);
		~Font();
		virtual bool Create(std::string filename, ...) override;
		bool Load(const std::string& filename, int fontSize);
	private:
		_TTF_Font* m_ttfFont = nullptr;

	};
}