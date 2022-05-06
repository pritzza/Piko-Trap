#include "Game.h"

#include <iostream>

#include "event/GameStateMachineOperationEvent.h"
#include "event/EntityCollisionEvent.h"

Game::Game(
	const int width,
	const int height,
	const unsigned frameRate,
	const std::string& name,
	const int windowStyle)
	:
	data{ gameStateMachine, eventBus, physicsHandler, window, renderer, timer, this->targetFrameRate, isRunning },
	window{ width, height, name, windowStyle },
	renderer{ window },
	targetFrameRate{ frameRate }
{}

void Game::loop()
{
	// init junk

	// set up event subscribers

	this->eventBus.subscribe(&this->gameStateMachine, &GameStateMachine::handleOperationEvent);
	this->eventBus.subscribe(&this->physicsHandler, &PhysicsHandler::handleEntityCollision);

	// set up initial gamestate

	GameStateMachineOperationEvent addStartingState{ { GameStateMachineOperationType::AddState, GameStateID::Platform } };
	GameStateMachineOperationEvent changeToStartingState{ { GameStateMachineOperationType::ChangeCurrentState, GameStateID::Platform} };

	this->eventBus.publish(&addStartingState);
	this->eventBus.publish(&changeToStartingState);

	this->gameStateMachine.processChanges();

	// gameloop
	while (this->isRunning)
	{
		this->timer.wait(this->targetFrameRate);

		this->gameStateMachine.processChanges();

		this->window.update();

		this->gameStateMachine.getCurrentState().handleInput();
		this->gameStateMachine.getCurrentState().update(this->timer.getDeltaTime());
		this->gameStateMachine.getCurrentState().render();
	}
}