#pragma once

#include <memory>
#include <vector>

#include "../entity/Entity.h"

enum class Tile;

class Level
{
private:
	std::unique_ptr<Tile[]> tiles;

	int width{};
	int height{};
	int size{};

	std::vector<Entity> entites;

public:
	void load(int w, int h);

	const Tile* const getTileData() const { return this->tiles.get(); }

	const int getSize()	const	{ return this->size;	}
	const int getWidth() const	{ return this->width;	}
	const int getHeight() const	{ return this->height;	}
};