#pragma once
#include <string>
struct _TTF_Font;
namespace cg
{
	class Font
	{
		friend class Text;
	public:
		Font() = default;
		Font(const std::string& filename, int fontSize);
		~Font();
		void Load(const std::string& filename, int fontSize);
	private:
		_TTF_Font* m_ttfFont = nullptr;
	};
}