#pragma once

#include "logger/StdLogger.h"
#include "event/Event.h"
#include "sdl_wrapper/SDLWrapper.h"
#include "common/Size.h"
#include "common/Rng.h"
#include "atlas/Atlas.h"
#include "atlas/NoAtlasSpaceException.h"

class Game {

    SDLWrapper      sdlWrapper;
    Rng             rng;
    Atlas           atlas;

    void            Render();
    void            Update();

public:

    explicit        Game(const Size& windowSize);
    void            Loop();


};
