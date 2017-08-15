#pragma once

#include <vector>

#include "map/tile/Tile.h"
#include "PathNode.h"
#include "Waypoint.h"

namespace unnamed::map {

class Path {

    int                    arrivalRadius;
    std::vector<Waypoint>  waypoints;



    Waypoint&           GetCurrentWaypoint(const Point& pos);

public:

                        Path(PathNode* dest, int arrivalRadius_);

    Size<double>        GetMoveOffset(const Point& pos);
    bool                ReachedDestination() const;

};

}
