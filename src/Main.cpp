#include <iostream>

#include "Game.h"


int main(int argc, char** argv) {
    unnamed::Game game{ unnamed::Size<int> { 1024, 768 } };

    game.Loop();

    return 0;
}
