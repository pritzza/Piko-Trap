#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

struct Sprite
{
public:
	sf::Sprite sfSprite;
	sf::RectangleShape spriteBorder;

	bool flipHorizontally{ false };
	bool flipVertically{ false };

	// TODO: animation stuff too

	void init(const sf::Vector2f& pos = { 0, 0 });	//todo take in SpriteID to get texture n stuff

	void update(const sf::Vector2f& pos);

	const sf::Sprite& getSprite() const				{ return this->sfSprite;	 }
	const sf::RectangleShape& getBorder() const		{ return this->spriteBorder; }

};