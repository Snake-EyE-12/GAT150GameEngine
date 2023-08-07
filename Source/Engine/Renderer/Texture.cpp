#include "Texture.h"
#include "Renderer.h"
#include "SDL2-2.28.0/include/SDL_image.h"
namespace cg
{
	Texture::~Texture()
	{
		if (m_texture) SDL_DestroyTexture(m_texture);
	}
	bool Texture::Load(const std::string filename, Renderer& renderer)
	{
		SDL_Surface* surface = IMG_Load(filename.c_str());
		if (!surface)
		{
			// LOG_WARNING
			return false;
		}
		m_texture = SDL_CreateTextureFromSurface(renderer.m_renderer, surface);
		SDL_FreeSurface(surface);
		if (!m_texture)
		{
			// LOG_WARNING
			return false;
		}
		return true;
	}
	Vector2 Texture::GetSize()
	{
		// ASSERT texture is not null
		SDL_Point point;
		SDL_QueryTexture(m_texture, NULL, NULL, &(point.x), &(point.y));
		return Vector2{ point.x, point.y };
	}


	bool Texture::Create(std::string filename, ...)
	{
		va_list args;
		va_start(args, filename);
		Renderer& renderer = va_arg(args, Renderer);
		va_end(args);
		return Load(filename, renderer);
	}
}