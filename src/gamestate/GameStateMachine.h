#pragma once

#include <memory>
#include <unordered_map>
#include <queue>

#include "GameState.h"
#include "GameStateMachineOperation.h"

#include "../event/GameStateMachineOperationEvent.h"	// TODO fix dependancy hell

class GameStateMachineOperationEvent;

enum class GameStateID;

struct GameData;

class Event;

class GameStateMachine
{
private:
	std::unordered_map<GameStateID, std::unique_ptr<GameState>> states;

	GameStateID currentStateID;

	std::queue<GameStateMachineOperation> operationQueue;

	GameData& gameData;

private:
	void changeState(const GameStateID id);	// changes the current state without modifying any other existing states
	void addState(const GameStateID id);	// inserts a new state at a STATE_ID key
	void removeState(const GameStateID id);	// removes a state at a STATE_ID key

	void enqueueOperation(const GameStateMachineOperation& operation); // done through handleOperation function
public:
	GameStateMachine(GameData& gameData)
		:
		gameData{ gameData } 
	{}

	void handleOperationEvent(const GameStateMachineOperationEvent* const e)
	{
		this->enqueueOperation(e->operation);
	}
	
	void processChanges();	// iterates through operationQueue to see what operations need to be done

	GameState& getCurrentState() const;

	const bool isLoaded(const GameStateID id) const;
};