#pragma once

#include <memory>

#include "common/Point.h"
#include "common/Color.h"
#include "common/Rng.h"
#include "common/StringFormat.h"
#include "atlas/Atlas.h"
#include "atlas/Element.h"
#include "sdl_wrapper/Wrapper.h"
#include "logger/StdLogger.h"
#include "Rock.h"

#define TILE_SIZE 50

namespace unnamed::map {

enum class Direction {
    NORTH = 0,
    EAST = 1,
    SOUTH = 2,
    WEST = 3,
    NORTH_EAST = 4,
    SOUTH_EAST = 5,
    SOUTH_WEST = 6,
    NORTH_WEST = 7
};

class Tile {

    Rect                            rect;
    Tile*                           neighbour[4];
    std::shared_ptr<atlas::Element> sprite;
    std::unique_ptr<Rock>           rock;

public:

                        Tile(const Point& pos, std::shared_ptr<atlas::Element>& sprite_);
        void            SetNeighbour(Direction dir, Tile* tile);

        Tile*           GetNeighbour(Direction dir) const;
        Tile*           GetNeighbourByPoint(const Point& p) const;
        Point           GetPos() const;
        Rect            GetRect() const;
        void            Draw(const Point& camera, const Point& offset);
        void            AddRock(std::unique_ptr<Rock> rock_);
        bool            HasRock() const;
        bool            IsTraversable() const;
        void            MarkRed();

 };

void LinkRows(Tile* topRow, Tile* botRow);

}
