#pragma once

#include "GameState.h"

#include <SFML/Graphics.hpp>

#include "../entity/Entity.h"
#include "../level/Level.h"

class GameStateTitle : public GameState
{
private:
	// TODO

protected:
	void virtual load();
	void virtual unload();

public:
	GameStateTitle(GameData& data) : GameState{ data } {}

	void virtual handleInput();		// makes events based on keyboard input
	void virtual update(const double dt, const double pt = 0);	// updates all objects of state
	void virtual render() const;
};