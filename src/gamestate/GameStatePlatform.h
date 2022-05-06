#pragma once

#include "GameState.h"

#include "../entity/Entity.h"
#include "../level/Level.h"

class GameStatePlatform : public GameState
{
private:
	Entity p1;
	Entity p2;

	Level level;

protected:
	void virtual load();
	void virtual unload();

public:
	GameStatePlatform(GameData& data) : GameState{ data } {}

	void virtual handleInput();		// makes events based on keyboard input
	void virtual update(const double dt, const double pt = 0);	// updates all objects of state
	void virtual render() const;
};