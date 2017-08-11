#pragma once

#include <vector>

#include "map/Tile.h"
#include "PathNode.h"

class Path {

    std::vector<Tile*>  waypoints;

public:

    explicit            Path(PathNode* dest);

    Tile*               GetNextTile();

};
