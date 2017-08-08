#pragma once

#include "logger/StdLogger.h"
#include "event/Event.h"
#include "sdl_wrapper/SDLWrapper.h"
#include "common/Size.h"
#include "atlas/Atlas.h"

class Game {

    SDLWrapper      sdlWrapper;
    Atlas           atlas;

    void            Render();
    void            Update();

public:

    explicit        Game(const Size& windowSize);
    void            Loop();


};
