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

namespace unnamed {

class Game {

    sdl::SDLWrapper             sdlWrapper;
    rng::Rng                    rng;
    atlas::Atlas                atlas;
    map::LandscapeGenerator     landscapeGenerator;
    map::Map                    map;


    void            Render();
    void            Update();
    void            HandleKeyDown(event::EventKeyDown& event);

public:

    explicit        Game(const Size& windowSize);
    void            Loop();
};

}
