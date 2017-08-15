#pragma once

#include <memory>

#include "common/Point.h"
#include "common/Rect.h"
#include "atlas/Element.h"
#include "map/pathfinding/Path.h"
#include "map/pathfinding/FindPath.h"
#include "map/tile/Tile.h"

namespace unnamed::unit {


class Unit {

    map::Tile*                      currTile;
    Point                           position;
    int                             speed;
    std::shared_ptr<atlas::Element> sprite;
    std::unique_ptr<map::Path>      currDest;


    void                            SetPos(const Point& newPos);

public:

                        Unit(map::Tile* initialTile, std::shared_ptr<atlas::Element>& sprite_);

    bool                HasDestination() const;
    void                SetDestination(map::Tile* destTile);
    void                WalkDestination();
    void                UpdateTile();

    map::Tile*          GetTile() const;
    Point               GetPos() const;
    void                Move(const Size<double>& normalizedOffset);

    void                Draw(const Point& camera, const Point& offset);

};


}
