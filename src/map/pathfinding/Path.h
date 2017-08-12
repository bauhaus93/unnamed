#pragma once

#include <vector>

#include "map/tile/Tile.h"
#include "PathNode.h"
#include "Waypoint.h"

namespace unnamed::map {

class Path {

    std::vector<Waypoint>  waypoints;


    Waypoint&           GetCurrentWaypoint(const Point& pos);

public:

    explicit            Path(PathNode* dest);

    Size<double>        GetMoveOffset(const Point& pos);
    bool                ReachedDestination() const;

};

}
