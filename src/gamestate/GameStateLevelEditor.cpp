#include "GameStateLevelEditor.h"

#include <iostream>

#include "../Game.h"

void GameStateLevelEditor::load()
{
	std::cout << "Editor load\n";
}

void GameStateLevelEditor::unload()
{
	std::cout << "Editor unload\n";
}

void GameStateLevelEditor::handleInput()
{
	std::cout << "Editor input\n";

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

void GameStateLevelEditor::update(const double dt, const double pt)
{
	std::cout << "Editor update\n";
}

void GameStateLevelEditor::render() const
{
	std::cout << "Editor render\n";
}