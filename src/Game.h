#pragma once

#include "gfx/Renderer.h"
#include "util/Window.h"

#include "gamestate/GameStateMachine.h"
#include "event/EventBus.h"
#include "physics/PhysicsHandler.h"
#include "util/Timer.h"

#include "GameData.h"

class Game
{
private:
	GameData data;

	GameStateMachine gameStateMachine{ data };

	EventBus eventBus;

	PhysicsHandler physicsHandler;

	Window window;
	Renderer renderer;

	Timer timer;

	unsigned targetFrameRate;	// TODO make delta time actually use this FPS var
	bool isRunning{ false };

private:
	void loop();

	inline void stop() { this->isRunning = false; }

public:
	Game(
		const int width,
		const int height,
		const unsigned frameRate,
		const std::string& name,
		const int windowStyle
	);

	inline void start() 
	{
		this->data.isRunning = true; 
		this->loop();
	}

};