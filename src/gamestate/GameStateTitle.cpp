#include "GameStateTitle.h"

#include <SFML/Window/Keyboard.hpp>

#include <iostream>

#include "../Game.h"

void GameStateTitle::load()
{
	std::cout << "Title load\n";
}

void GameStateTitle::unload()
{
	std::cout << "Title unload\n";
}

void GameStateTitle::handleInput()
{
	std::cout << "Title input\n";

	GameStateMachine& gsm{ this->data.gameStateMachine };
	EventBus bus{ this->data.eventBus };

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
	{
		if (gsm.isLoaded(GameStateID::Platform))
		{
			GameStateMachineOperationEvent addState{ GameStateMachineOperation(GameStateMachineOperationType::AddState, GameStateID::Platform) };
			bus.publish(&addState);
		}
		GameStateMachineOperationEvent changeState{ GameStateMachineOperation(GameStateMachineOperationType::ChangeCurrentState, GameStateID::Platform) };
		bus.publish(&changeState);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
	{
		if (gsm.isLoaded(GameStateID::LevelEditor))
		{
			GameStateMachineOperationEvent addState{ GameStateMachineOperation(GameStateMachineOperationType::AddState, GameStateID::Title) };
			bus.publish(&addState);
		}
		GameStateMachineOperationEvent changeState{ GameStateMachineOperation(GameStateMachineOperationType::ChangeCurrentState, GameStateID::Title) };
		bus.publish(&changeState);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
	{
		if (gsm.isLoaded(GameStateID::LevelEditor))
		{
			GameStateMachineOperationEvent addState{ GameStateMachineOperation(GameStateMachineOperationType::AddState, GameStateID::LevelEditor) };
			bus.publish(&addState);
		}
		GameStateMachineOperationEvent changeState{ GameStateMachineOperation(GameStateMachineOperationType::ChangeCurrentState, GameStateID::LevelEditor) };
		bus.publish(&changeState);
	}
}

void GameStateTitle::update(const double dt, const double pt)
{
	std::cout << "Title update\n";
}

void GameStateTitle::render() const
{
	std::cout << "Title render\n";
}