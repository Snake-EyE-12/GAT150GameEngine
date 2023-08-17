#pragma once
#include "Core/Core.h"
#include <vector>
#include "Framework/Resource/Resource.h"

namespace cg
{
	class Renderer;

	class Model : public Resource
	{
	public:
		Model() = default;
		Model(const std::vector<Vector2>& points) : m_points{ points } {}

		bool Load(const std::string& filename);
		void Draw(Renderer& renderer, const vec2& position, float rotation, float scale);
		void Draw(Renderer& renderer, const Transform& transform);
		float GetRadius();
		Color GetColor();
		virtual bool Create(std::string filename, ...) override;
	private:
		std::vector<vec2> m_points;
		Color m_color;
		float m_radius = 0;
	};
}