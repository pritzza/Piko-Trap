#pragma once

#include "Event.h"

#include "../gamestate/GameStateMachineOperation.h"

struct GameStateMachineOperationEvent : public Event
{
	const GameStateMachineOperation operation;

	GameStateMachineOperationEvent(const GameStateMachineOperation& operation) 
		:
		operation{ operation } 
	{}
};