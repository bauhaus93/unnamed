#pragma once

#include "logger/StdLogger.h"
#include "event/Event.h"
#include "event/EventKeyDown.h"
#include "sdl_wrapper/Wrapper.h"
#include "common/Size.h"
#include "common/Rng.h"
#include "atlas/Atlas.h"
#include "atlas/NoAtlasSpaceException.h"
#include "map/Map.h"
#include "map/generator/LandscapeGenerator.h"
#include "unit/UnitManager.h"
#include "map/pathfinding/FindPath.h"
#include "frequency_handler/FrequencyHandler.h"

namespace unnamed {

class Game {

    sdl::Wrapper                        sdlWrapper;
    rng::Rng                            rng;
    atlas::Atlas                        atlas;
    map::LandscapeGenerator             landscapeGenerator;
    map::Map                            map;
    unit::UnitManager                   unitManager;
    freq::FrequencyHandler              fpsHandler;
    freq::FrequencyHandler              upsHandler;


    void            Render();
    void            Update();
    void            HandleKeyDown(event::EventKeyDown& event);
    void            HandleUnits();

public:

    explicit        Game(const Size<int>& windowSize);
    void            Loop();
};

}
