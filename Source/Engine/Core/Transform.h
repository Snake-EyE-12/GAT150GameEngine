#pragma once
#include "Vector2.h"

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
	};


}