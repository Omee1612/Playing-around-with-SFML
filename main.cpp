#include <iostream>
#include "game.h"

int main() {
    std::srand(static_cast<unsigned>(time(NULL)));
    Game game;
    while (game.running())
    {
        //Update
        game.update();
        //Render
        game.render();
    }
    // End
    return 0;
}
