#include "Window.h"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

Window::Window(const int width, const int height, const std::string& name, const int style)
    :
    window{ sf::VideoMode(width, height), name, sf::Style::Default | sf::Style::Resize },
    width{ width },
    height{ height }
{}

void Window::pollEvents()
{
	sf::Event event;

	if (this->window.pollEvent(event))
		switch (event.type)
		{
		case sf::Event::Closed:			this->window.close();		break;
		case sf::Event::GainedFocus:	this->focused = true;		break;
		case sf::Event::LostFocus:		this->focused = false;		break;
		}
}

void Window::update()
{
	this->pollEvents();
}

void Window::clear(const sf::Color clearColor = sf::Color{ 0, 0, 0, 255})
{
	this->window.clear(clearColor);
}

void Window::display()
{
	this->window.display();
}

void Window::draw(const sf::Drawable& sprite)
{
	this->window.draw(sprite);
}