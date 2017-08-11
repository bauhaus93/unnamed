#pragma once

#include "atlas/Atlas.h"
#include "sdl_wrapper/Wrapper.h"
#include "logger/StdLogger.h"
#include "common/Point.h"
#include "common/Rect.h"
#include "pathfinding/FindPath.h"
#include "Tile.h"
#include "generator/LandscapeGenerator.h"

namespace unnamed::map {

class Map {

    Size                            size;
    generator::LandscapeGenerator&  landscapeGenerator;
    Tile*                           root;
    Tile*                           camera;


public:

                        Map(const Size& size_, generator::LandscapeGenerator& landscapeGenerator_);
                        ~Map();
    void                Draw(const Rect& destRect);
    void                MoveCamera(Direction dir);

};

}
