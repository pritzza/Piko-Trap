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
	tileSprite.sfSprite.setFillColor(sf::Color{ 123,111,213 });
	tileSprite.sfSprite.setOutlineColor(sf::Color{ 123,111,213 });

	static constexpr int TILE_LEN{ 100 };

	const Tile* const tileData{ level.getTileData() };

	for (int i = 0; i < size; ++i)
	{
		const Tile& tile{ tileData[i] };

		// dont need to do this work for tile we dont draw
		//if (tile != Tile::Air)
		{
			const int x{ (i % w) * TILE_LEN };
			const int y{ (i / w) * TILE_LEN };

			tileSprite.setPos(sf::Vector2f(x, y));

			this->window.draw(tileSprite.getSprite());
		}
	}
}

void Renderer::render(const Sprite& sprite)
{
	this->window.draw(sprite.getSprite());
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
