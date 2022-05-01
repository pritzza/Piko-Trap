#include "Entity.h"

void Entity::init(const AABB& aabb)
{
	this->pos = sf::Vector2f( aabb.x, aabb.y );

	this->initSprite(aabb);
	this->initAABB(aabb);
}

void Entity::initSprite(const AABB& aabb)
{
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
	this->sprite.setPos(this->pos);
	this->sprite.update();

	this->aabbRect.setPosition(this->pos);
}