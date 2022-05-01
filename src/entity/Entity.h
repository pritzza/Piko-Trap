#pragma once

#include <SFML/System/Vector2.hpp>
#include "../util/AABB.h"

#include "../gfx/sprite/Sprite.h"

class Entity
{
private:
	sf::Vector2f pos;
	sf::Vector2f vel;

	Sprite sprite;

	AABB aabb;
	sf::RectangleShape aabbRect;

public:
	void init(const AABB& aabb);
	void initSprite(const AABB& aabb);
	void initAABB(const AABB& aabb);

	void update(const float dt);

	void setPos(const sf::Vector2f pos) { this->pos = pos;		}
	const sf::Vector2f& getPos() const	{ return this->pos;		}

	void setVel(const sf::Vector2f vel) { this->vel = vel;		}
	const sf::Vector2f& getVel() const	{ return this->vel;		}

	const Sprite& getSprite() const		{ return this->sprite;	}
	const AABB& getAABB() const			{ return this->aabb;	}

};