#pragma once

#include "sprite/Sprite.h" // TODO WHYYYYY???? an hour wasted here
class Window;

class Level;

// renderer's purpose is to render sprites and pass the result to the window
class Renderer
{
private:
	Window& window;

public:
	Renderer(Window& window);

	void render(const Level& level);
	void render(const Sprite& sprite); // TODO why does this give link error if const arg
	void preRender();	// clears the screen
	void postRender();	// displays the screen

};