#include <ctime>

#include "snake/Game.h"

int main() {
    srand(time(nullptr));

    Snake::Game game;
    game.Run();

    return 0;
}
