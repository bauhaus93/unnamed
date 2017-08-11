#pragma once

#include <vector>

#include "map/Tile.h"
#include "PathNode.h"

namespace unnamed::map::pathfinding {

class Path {

    std::vector<Tile*>  waypoints;

public:

    explicit            Path(PathNode* dest);

    map::Tile*          GetNextTile();

};

}
