#include "Game.h"

#include <iostream>

#include "event/GameStateMachineOperationEvent.h"
#include "event/EntityCollisionEvent.h"

#include "resourcemanager/TextureResource.h"
#include "resourcemanager/ResourceManager.h"

Game::Game(
	const int width,
	const int height,
	const unsigned frameRate,
	const std::string& name,
	const int windowStyle)
	:
	// TODO make this and the inner structure of Game/GameData more scaleable
	data{ gameStateMachine, textureManager, eventBus, physicsHandler, window, renderer, timer, this->targetFrameRate, isRunning },
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

	GameStateMachineOperationEvent addStartingState
	{ 
		GameStateMachineOperation{ GameStateMachineOperationType::AddState, GameStateID::Platform } 
	};

	GameStateMachineOperationEvent changeToStartingState
	{ 
		GameStateMachineOperation{ GameStateMachineOperationType::ChangeCurrentState, GameStateID::Platform }
	};

	this->eventBus.publish(&addStartingState);
	this->eventBus.publish(&changeToStartingState);

	this->gameStateMachine.processChanges();

	// Texture Resource test
	TextureResource t;
	t.load("res/untitled.png");
	t.get();
	t.unload();

	EnumArray<TextureID,int>::test();

	// TODO write unit tests
	textureManager.get(TextureID::Test1);
	textureManager.unload(TextureID::Test1);

	// gameloop
	while (this->isRunning)
	{
		this->timer.wait(this->targetFrameRate);

		this->gameStateMachine.processChanges();

		// TODO make game stop when window is closed
		this->window.update();

		this->gameStateMachine.getCurrentState().handleInput();
		this->gameStateMachine.getCurrentState().update(this->timer.getDeltaTime());
		this->gameStateMachine.getCurrentState().render();
	}
}