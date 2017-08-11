#pragma once

#include <memory>

#include "sdl_wrapper/SDLWrapper.h"
#include "common/Rect.h"
#include "atlas/Atlas.h"
#include "SimplexNoise.h"
#include "Tile.h"

namespace unnamed::map {

class LandscapeGenerator {

    sdl::SDLWrapper&        sdlWrapper;
    atlas::Atlas&           atlas;
    rng::Rng                rng;
    SimplexNoise            floorVariationNoise;
    SimplexNoise            rockNoise;

    Tile*                   CreateTile(const Rect& tileRect);
    atlas::AtlasElement&    CreateFloorSprite(const Rect& tileRect);
    atlas::AtlasElement&    CreateRockSprite(const Rect& rect, uint8_t rockMask);
    bool                    HasRock(const Rect& tileRect);
    uint8_t                 GetNeighbourRockMask(const Rect& tileRect);

public:
                            LandscapeGenerator(sdl::SDLWrapper& sdlWrapper_, atlas::Atlas& atlas, unsigned int seed);
    Tile*                   Generate(const Rect& fieldRect);

};

}
