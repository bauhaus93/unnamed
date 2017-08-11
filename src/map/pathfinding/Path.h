#pragma once

#include <vector>

#include "map/tile/Tile.h"
#include "PathNode.h"

namespace unnamed::map {

class Path {

    std::vector<Tile*>  waypoints;

public:

    explicit            Path(PathNode* dest);

    map::Tile*          GetNextTile();

};

}
