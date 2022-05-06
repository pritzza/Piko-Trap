#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include <cstdint>

class Renderer;

class Window
{
private:
	sf::RenderWindow window;

	const int width;
	const int height;

	bool focused{ true };

private:
	void pollEvents();

private:
	// methods intended for solely Renderer's use
	void clear(const sf::Color clearColor);
	void display();
	void draw(const sf::Drawable& sprite);

public:
	Window(const int width, const int height, const std::string& name, const int style);

	void update();

	inline const int getWidth() const				{ return this->width;			}
	inline const int getHeight() const				{ return this->height;			}
	inline const sf::RenderWindow& getWindow() const	{ return this->window;			}

	inline const bool isFocused() const					{ return this->focused;			}
	inline const bool isOpen() const					{ return this->window.isOpen(); }

	friend class Renderer;
};