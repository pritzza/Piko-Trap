#pragma once

#include <SFML/Window/WindowStyle.hpp>

#include "gfx/Renderer.h"

#include "util/Window.h"
#include "util/DeltaTime.h"
#include "gamestate/GameStateMachine.h"

#include "event/EventBus.h"

#include "physics/PhysicsHandler.h"

struct GameData
{
	GameStateMachine& gameStateMachine;

	EventBus& eventBus;

	PhysicsHandler& physicsHandler;

	Window& window;
	Renderer& renderer;

	DeltaTime& dt;

	uint8_t& frameRate;

	bool& isRunning;
};

class Game
{
private:
	GameData data;

	GameStateMachine gameStateMachine{ data };

	EventBus eventBus;

	PhysicsHandler physicsHandler;

	Window window;
	Renderer renderer;

	DeltaTime dt;

	uint8_t frameRate;	// TODO make delta time actually use this FPS var
	bool isRunning;

private:
	void loop();

	inline void stop() { this->isRunning = false; }

public:
	Game(
		const uint16_t width,
		const uint16_t height,
		const uint8_t frameRate,
		const std::string& name,
		const int windowStyle
	);

	inline void start() 
	{
		this->data.isRunning = true; 
		this->loop();
	}

};