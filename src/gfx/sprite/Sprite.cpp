#include "Sprite.h"

void Sprite::init(const sf::Vector2f& pos)
{
	// sprite border will have the same size as the sprite
	const sf::IntRect& r{ this->sfSprite.getTextureRect() };
	const sf::Vector2f spriteSize( r.width - r.left, r.height - r.top );

	this->spriteBorder.setSize(spriteSize);
	this->spriteBorder.setSize(sf::Vector2f{100,100});	// TODO remove

	this->spriteBorder.setFillColor(sf::Color::Transparent);
	this->spriteBorder.setOutlineColor(sf::Color{ 0, 0, 0 });
	this->spriteBorder.setOutlineThickness(1.f);

	this->update(pos);
}

void Sprite::update(const sf::Vector2f& pos)
{
	this->sfSprite.setPosition(pos);
	this->spriteBorder.setPosition(pos);
}

void Sprite::setTexture(const sf::Texture& texture)
{
	this->sfSprite.setTexture(texture);
}
