#pragma once

#include "common/Point.h"
#include "common/Color.h"
#include "common/Rng.h"
#include "common/StringFormat.h"
#include "atlas/Atlas.h"
#include "atlas/AtlasElement.h"
#include "sdl_wrapper/SDLWrapper.h"
#include "logger/StdLogger.h"


#define TILE_SIZE 50

enum class Direction {
    NORTH = 0,
    EAST = 1,
    SOUTH = 2,
    WEST = 3
};

class Tile {

    Rect                rect;
    Tile*               neighbour[4];
    AtlasElement&       sprite;

public:

                        Tile(const Point& pos, Atlas& atlas, SDLWrapper& sdlWrapper);
        void            SetNeighbour(Direction dir, Tile* tile);
        void            ExpandRow(int count, Atlas& atlas, SDLWrapper& sdlWrapper);
        void            ExpandColumn(int count, Atlas& atlas, SDLWrapper& sdlWrapper);

        Tile*           GetNeighbour(Direction dir) const;
        Point           GetPos() const;
        void            Draw(const Point& camera, const Point& offset);

 };

void LinkRows(Tile* topRow, Tile* botRow);
