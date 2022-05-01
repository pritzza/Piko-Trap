#include "GameStateMachine.h"

#include "GameStateIDs.h"

#include "GameStatePlatform.h"
#include "GameStateTitle.h"
#include "GameStateLevelEditor.h"

#include <iostream>

#include "../event/Event.h"
#include "../event/GameStateMachineOperationEvent.h"

void GameStateMachine::changeState(const GameStateID id)
{
	if (states.find(id) != states.end())	// only change to a state that exists
		currentStateID = id;
}

void GameStateMachine::addState(const GameStateID id)
{
	if (states.find(id) == states.end())		// only add a state if it doesnt exist yet
		switch (id)
		{
		case GameStateID::Platform:		states.insert({ id, std::make_unique<GameStatePlatform>(gameData) });		break; // THANK YOU IDE
		case GameStateID::Title:		states.insert({ id, std::make_unique<GameStateTitle>(gameData) });			break;
		case GameStateID::LevelEditor:	states.insert({ id, std::make_unique<GameStateLevelEditor>(gameData) });	break;
		}

	states.at(id).get()->load();
}

void GameStateMachine::removeState(const GameStateID id)
{
	if (states.find(id) != states.end())	// only remove state that does exist
	{
		states.at(id).get()->unload();
		states.erase(id);
	}
}

void GameStateMachine::processChanges()
{
	while (operationQueue.empty() == false)
	{
		const GameStateMachineOperation& op{ operationQueue.front() };

		switch (op.type)
		{
		case GameStateMachineOperationType::AddState:			addState(op.state);				break;
		case GameStateMachineOperationType::RemoveState:		removeState(op.state);			break;
		case GameStateMachineOperationType::ChangeCurrentState:	changeState(op.state);			break;
		}

		operationQueue.pop();
	}
}

void GameStateMachine::enqueueOperation(const GameStateMachineOperation& operation)
{
	operationQueue.push(operation);
}

GameState& GameStateMachine::getCurrentState() const
{
	return *states.at(currentStateID).get();
}

const bool GameStateMachine::isLoaded(const GameStateID id) const
{
	return (this->states.find(id) == this->states.end());
}

