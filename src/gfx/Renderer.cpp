#include "Renderer.h"

#include "sprite/Sprite.h"
#include "../util/Window.h"

#include "../level/Level.h"

#include "../level/Tile.h"

#include <iostream>

Renderer::Renderer(Window& window)
	:
	window{ window }
{}

void Renderer::render(const Level& level)
{
	const int size{ level.getSize() };
	const int w{ level.getWidth() };

	Sprite tileSprite;
	tileSprite.init(sf::Vector2f(0, 0));

	static constexpr int TILE_LEN{ 100 };

	const Tile* const tileData{ level.getTileData() };

	for (int i = 0; i < size; ++i)
	{
		const Tile& tile{ tileData[i] };

		if (tile != Tile::Air)
		{
			const int x{ (i % w) * TILE_LEN };
			const int y{ (i / w) * TILE_LEN };

			tileSprite.update(sf::Vector2f(x, y));

			// TODO I would like for the sprites(?) of each tile to be rendered
			// I think this means each Tile stores its own sprite??
			this->window.draw(tileSprite.getSprite());
			this->window.draw(tileSprite.getBorder());
		}
	}
}

void Renderer::render(const Sprite& sprite)
{
	this->window.draw(sprite.getSprite());
	this->window.draw(sprite.getBorder());
}

void Renderer::preRender()
{
	static const sf::Color CLEAR_COLOR{ 255, 0, 255 };
	this->window.clear(CLEAR_COLOR);
}

void Renderer::postRender()
{
	this->window.display();
}
