#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

struct Sprite
{
public:
	//sf::Sprite sprite;
	sf::RectangleShape sfSprite;
	sf::Vector2f pos;
	bool flipHorizontally{ false };
	bool flipVertically{ false };

	// animation stuff too

	void init(const sf::Vector2f& pos);	//todo take in SpriteID to get texture n stuff

	void update();

	void setPos(const sf::Vector2f& pos)	{ this->pos = pos;	}
	const sf::Vector2f& getPos() const		{ return this->pos; }

	const sf::RectangleShape& getSprite() const { return this->sfSprite; }
};