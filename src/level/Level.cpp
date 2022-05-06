#include "Level.h"

#include "Tile.h"

void Level::load(int width, int height)
{
	this->width = width;
	this->height = height;
	this->size = width * height;
	tiles = std::make_unique<Tile[]>(size);	// makes m_cells point to array of [width * height] uint8_t's

	for (int i = 0; i < size; ++i)
	{
		if (i%3)
			tiles[i] = Tile::Air;
		else
			tiles[i] = Tile::Solid;
	}
}
