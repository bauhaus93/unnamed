#pragma once

#include <memory>

#include "sdl_wrapper/SDLWrapper.h"
#include "common/Rect.h"
#include "atlas/Atlas.h"
#include "SimplexNoise.h"
#include "Tile.h"

class LandscapeGenerator {

    SDLWrapper&             sdlWrapper;
    Atlas&                  atlas;
    Rng                     rng;
    SimplexNoise            floorVariationNoise;
    SimplexNoise            rockNoise;

    Tile*                   CreateTile(const Rect& tileRect);
    AtlasElement&           CreateFloorSprite(const Rect& tileRect);
    AtlasElement&           CreateRockSprite(const Rect& rect, uint8_t rockMask);
    bool                    HasRock(const Rect& tileRect);
    uint8_t                 GetNeighbourRockMask(const Rect& tileRect);

public:
                            LandscapeGenerator(SDLWrapper& sdlWrapper_, Atlas& atlas, unsigned int seed);
    Tile*                   Generate(const Rect& fieldRect);

};
