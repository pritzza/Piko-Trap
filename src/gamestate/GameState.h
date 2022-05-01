#pragma once

struct GameData;

class GameState
{
protected:
	GameData& data;

protected:
	void virtual load() = 0;
	void virtual unload() = 0;

public:
	GameState(GameData& gameData) : data{ gameData } {}

	void virtual handleInput() = 0;		// makes events based on keyboard input
	void virtual update(const double dt, const double pt = 0) = 0;	// updates all objects of state
	void virtual render() const = 0;

	friend class GameStateMachine;
};