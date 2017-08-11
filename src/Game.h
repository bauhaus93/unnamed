#pragma once

#include "logger/StdLogger.h"
#include "event/Event.h"
#include "event/EventKeyDown.h"
#include "sdl_wrapper/SDLWrapper.h"
#include "common/Size.h"
#include "common/Rng.h"
#include "atlas/Atlas.h"
#include "atlas/NoAtlasSpaceException.h"
#include "map/Map.h"
#include "map/LandscapeGenerator.h"


class Game {

    SDLWrapper          sdlWrapper;
    Rng                 rng;
    Atlas               atlas;
    LandscapeGenerator  landscapeGenerator;
    Map                 map;


    void            Render();
    void            Update();
    void            HandleKeyDown(EventKeyDown& event);

public:

    explicit        Game(const Size& windowSize);
    void            Loop();


};
