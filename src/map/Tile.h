#pragma once

#include <memory>

#include "common/Point.h"
#include "common/Color.h"
#include "common/Rng.h"
#include "common/StringFormat.h"
#include "atlas/Atlas.h"
#include "atlas/AtlasElement.h"
#include "sdl_wrapper/SDLWrapper.h"
#include "logger/StdLogger.h"
#include "Rock.h"

#define TILE_SIZE 50

enum class Direction {
    NORTH = 0,
    EAST = 1,
    SOUTH = 2,
    WEST = 3
};

class Tile {

    Rect                    rect;
    Tile*                   neighbour[4];
    AtlasElement&           sprite;
    std::unique_ptr<Rock>   rock;

public:

                        Tile(const Point& pos, AtlasElement& sprite_);
        void            SetNeighbour(Direction dir, Tile* tile);

        Tile*           GetNeighbour(Direction dir) const;
        Point           GetPos() const;
        void            Draw(const Point& camera, const Point& offset);
        void            AddRock(std::unique_ptr<Rock> rock_);
        bool            HasRock() const;

 };

void LinkRows(Tile* topRow, Tile* botRow);
