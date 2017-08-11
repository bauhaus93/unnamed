#pragma once

#include <memory>

#include "common/Point.h"
#include "common/Rect.h"
#include "atlas/Element.h"
#include "map/pathfinding/Path.h"
#include "map/tile/Tile.h"

namespace unnamed::unit {


class Unit {

    map::Tile*                      currTile;
    Point                           position;
    std::shared_ptr<atlas::Element> sprite;
    std::unique_ptr<map::Path>      currDest;

    void                            SetPos(const Point& newPos);

public:

                        Unit(map::Tile* initialTile, std::shared_ptr<atlas::Element>& sprite_);

    bool                HasDestination() const;
    void                SetDestination(std::unique_ptr<map::Path> destination);
    void                WalkDestination();

    map::Tile*          GetTile() const;
    Point               GetPos() const;

    void                Draw(const Point& camera, const Point& offset);

};


}
