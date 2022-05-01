#include "Game.h"

int main()
{
    Game game{ 1280, 720, 60, "Game", sf::Style::Default };

    game.start();

    return 0;
}