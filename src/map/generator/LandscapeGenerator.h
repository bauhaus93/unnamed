#pragma once

#include <memory>

#include "sdl_wrapper/Wrapper.h"
#include "common/Rect.h"
#include "atlas/Atlas.h"
#include "SimplexNoise.h"
#include "map/Tile.h"

namespace unnamed::map::generator {

class LandscapeGenerator {

    sdl::Wrapper&           sdlWrapper;
    atlas::Atlas&           atlas;
    rng::Rng                rng;
    SimplexNoise            floorVariationNoise;
    SimplexNoise            rockNoise;

    Tile*                   CreateTile(const Rect& tileRect);
    atlas::Element&         CreateFloorSprite(const Rect& tileRect);
    atlas::Element&         CreateRockSprite(const Rect& rect, uint8_t rockMask);
    bool                    HasRock(const Rect& tileRect);
    uint8_t                 GetNeighbourRockMask(const Rect& tileRect);

public:
                            LandscapeGenerator(sdl::Wrapper& sdlWrapper_, atlas::Atlas& atlas, unsigned int seed);
    Tile*                   Generate(const Rect& fieldRect);

};

}