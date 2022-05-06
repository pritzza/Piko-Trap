#include "Entity.h"

#include "../gfx/Sprite/SpriteID.h"

void Entity::init(const sf::Vector2f& pos, const SpriteID spriteID, const AABB& aabb)
{
	this->pos = pos;

	this->initSprite(spriteID);
	this->initAABB(aabb);
}

void Entity::initSprite(const SpriteID spriteid)
{
	//this->sprite = s;
	this->sprite.init(this->pos);
}

void Entity::initAABB(const AABB& aabb)
{
	this->aabb = aabb;
	this->aabbRect.setSize(sf::Vector2f( aabb.w, aabb.h ));
	this->aabbRect.setFillColor(sf::Color{ 255, 0, 0, 25 });
}

void Entity::update(const float dt)
{
	// movement/physics
	this->pos += this->vel * dt;
	this->vel = sf::Vector2f( 0, 0 );

	// collider
	this->aabb.x = this->pos.x;
	this->aabb.y = this->pos.y;

	// sprite/graphics
	this->sprite.update(this->pos);

	this->aabbRect.setPosition(this->pos);
}