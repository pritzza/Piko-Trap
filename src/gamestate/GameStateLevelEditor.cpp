#include "GameStateLevelEditor.h"

#include <SFML/Window/Keyboard.hpp>

#include <iostream>

#include "GameStateMachine.h"
#include "../event/EventBus.h"

// TODO replace include game.h with only headers we need
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
		GameStateMachineOperationEvent changeState{ GameStateMachineOperation(GameStateMachineOperationType::ChangeCurrentState, GameStateID::Platform) };
		bus.publish(&changeState);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
	{
		GameStateMachineOperationEvent changeState{ GameStateMachineOperation(GameStateMachineOperationType::ChangeCurrentState, GameStateID::Title) };
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