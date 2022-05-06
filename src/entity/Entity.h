#pragma once

#include <SFML/System/Vector2.hpp>

#include "../gfx/sprite/Sprite.h"

#include "../util/AABB.h"

enum class SpriteID;

// Entity class represents any object/entity/thing in the game
// It has its a distinct sprite and collider
class Entity
{
private:
	sf::Vector2f pos{ 0, 0 };
	sf::Vector2f vel{ 0, 0 };

	Sprite sprite;

	AABB aabb{ 0, 0, 100, 100 };
	sf::RectangleShape aabbRect;

public:
	void init(const sf::Vector2f& pos, const SpriteID s, const AABB& aabb);
	void initSprite(const SpriteID spriteID);
	void initAABB(const AABB& aabb);

	void update(const float dt);

	void setPos(const sf::Vector2f pos) { this->pos = pos;		}
	const sf::Vector2f& getPos() const	{ return this->pos;		}

	void setVel(const sf::Vector2f vel) { this->vel = vel;		}
	const sf::Vector2f& getVel() const	{ return this->vel;		}

	const Sprite& getSprite() const		{ return this->sprite;	}
	const AABB& getAABB() const			{ return this->aabb;	}

};