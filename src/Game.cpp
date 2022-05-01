#include "Game.h"

#include <iostream>

#include "event/GameStateMachineOperationEvent.h"

Game::Game(
	const uint16_t width,
	const uint16_t height,
	const uint8_t frameRate,
	const std::string& name,
	const int windowStyle)
	:
	data{ gameStateMachine, eventBus, physicsHandler, window, renderer, dt, this->frameRate, isRunning },
	window{ width, height, name, windowStyle },
	renderer{ window },
	frameRate{ frameRate },
	isRunning{ false }
{}

void Game::loop()
{
	// init junk

	// set up event subscribers

	this->eventBus.subscribe(&physicsHandler, &PhysicsHandler::handleEntityCollision);
	this->eventBus.subscribe(&this->gameStateMachine, &GameStateMachine::handleOperationEvent);

	// set up initial gamestate

	GameStateMachineOperationEvent addStartingState{ { GameStateMachineOperationType::AddState, GameStateID::Platform } };
	GameStateMachineOperationEvent changeToStartingState{ { GameStateMachineOperationType::ChangeCurrentState, GameStateID::Platform} };

	eventBus.publish(&addStartingState);
	eventBus.publish(&changeToStartingState);

	this->gameStateMachine.processChanges();

	// gameloop
	while (this->isRunning)
	{
		this->dt.wait();

		this->gameStateMachine.processChanges();

		this->window.update();

		this->gameStateMachine.getCurrentState().handleInput();
		this->gameStateMachine.getCurrentState().update(dt.getDT());
		this->gameStateMachine.getCurrentState().render();
	}
}