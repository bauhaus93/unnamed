#include <iostream>

#include "Game.h"

using namespace std;

int main(int argc, char** argv) {
    Game game{ 1024, 768 };

    game.Loop();

    return 0;
}
