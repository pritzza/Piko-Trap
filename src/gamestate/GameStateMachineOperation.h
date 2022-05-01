#pragma once

#include "GameStateIDs.h"

enum class GameStateMachineOperationType
{
	AddState,
	RemoveState,
	ChangeCurrentState
};

struct GameStateMachineOperation
{
	const GameStateMachineOperationType type;
	const GameStateID state;

	GameStateMachineOperation(const GameStateMachineOperationType type, const GameStateID state)
		:
		type{ type },
		state{ state }
	{}
};