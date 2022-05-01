#include "Sprite.h"

void Sprite::init(const sf::Vector2f& pos)
{
	this->pos = pos;
	this->sfSprite.setSize(sf::Vector2f{100, 100});
	this->sfSprite.setFillColor(sf::Color{ 255, 129, 0 });

	update();
}

void Sprite::update()
{
	this->sfSprite.setPosition(this->pos);
}