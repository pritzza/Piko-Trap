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

	const uint16_t width;
	const uint16_t height;

	bool focused{ true };

private:
	void pollEvents();

private:
	// methods intended for solely Renderer's use
	void clear(const sf::Color clearColor);
	void display();
	void draw(const sf::Drawable& sprite);

public:
	Window(const uint16_t width, const uint16_t height, const std::string& name, const int style);

	void update();

	inline const uint16_t getWidth() const				{ return this->width;			}
	inline const uint16_t getHeight() const				{ return this->height;			}
	inline const sf::RenderWindow& getWindow() const	{ return this->window;			}

	inline const bool isFocused() const					{ return this->focused;			}
	inline const bool isOpen() const					{ return this->window.isOpen(); }

	friend class Renderer;
};