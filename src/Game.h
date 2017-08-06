#pragma once

#include "logger/StdLogger.h"
#include "event/Event.h"
#include "sdl_wrapper/SDLWrapper.h"

class Game {

    SDLWrapper      sdlWrapper;


    void            Render();
    void            Update();

public:

                    Game(int windowSizeX, int windowSizeY);
    void            Loop();


};
