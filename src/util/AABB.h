#pragma once

struct AABB
{
	int x, y, w, h;

	constexpr AABB(const int x, const int y, const int w, const int h)
		:
		x{ x },
		y{ y },
		w{ w },
		h{ h }
	{}

	inline const bool isColliding(const AABB& other) const
	{
		return x	 <= other.x + other.w &&
			   x + w >= other.x			  &&
			   y	 <= other.y + other.h &&
			   y + h >= other.y;
	}

	inline static constexpr bool collide(const AABB& a, const AABB& b)
	{										// from jdh
		return a.x		 <= b.x + b.w &&	// this.minX <= other.maxX &&
			   a.x + a.w >= b.x		  &&	// this.maxX >= other.minX &&
			   a.y		 <= b.y + b.h &&	// this.minY <= other.maxY &&
			   a.y + a.h >= b.y;			// this.maxY >= other.minY;
	}

	inline static constexpr bool isPointInside
	(
		const int px, const int py,
		AABB aabb
	)
	{
		return px >= aabb.x && px <= aabb.x + aabb.w &&
			   py >= aabb.y && py <= aabb.y + aabb.h;
	}
};