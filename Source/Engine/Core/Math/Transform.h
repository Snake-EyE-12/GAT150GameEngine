#pragma once
#include "Vector2.h"
#include "Matrix3x3.h"
#include "Core/Json.h"

namespace cg
{
	class Transform
	{
	public:
		Vector2 position;
		float rotation = 0;
		float scale = 1;

	public:
		Transform() = default;
		Transform(const Vector2& position, float rotation, float scale = 1.0f) :
			position{ position },
			rotation{ rotation },
			scale{ scale }
		{}
		Matrix3x3 GetMatrix() const {
			Matrix3x3 ms = Matrix3x3::CreateScale(scale);
			Matrix3x3 mr = Matrix3x3::CreateRotation(rotation);
			Matrix3x3 mt = Matrix3x3::CreateTranslation(position);
			return mt * ms * mr;
		}
		void Read(const json_t& value);
	};


}