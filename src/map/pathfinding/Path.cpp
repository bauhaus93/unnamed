#include "Path.h"

namespace unnamed::map {



Path::Path(PathNode* dest) {

    Tile* prevTile = nullptr;
    for (PathNode* curr = dest; curr != nullptr; curr = curr->GetPredecessor()) {
        Tile* currTile = curr->GetTile();

        if (waypoints.empty()) {
            waypoints.emplace_back();
            waypoints.back().SetEnd(currTile->GetPos());
        }
        else {
            Point currPos = currTile->GetPos();
            Point endPos = waypoints.back().GetEnd();

            if (curr->GetPredecessor() == nullptr) {
                currTile->MarkRed();
                waypoints.back().SetStart(currPos);
            }
            else if (currPos.x != endPos.x && currPos.y != endPos.y) {
                prevTile->MarkRed();
                waypoints.back().SetStart(prevTile->GetPos());
                waypoints.emplace_back();
                waypoints.back().SetEnd(prevTile->GetPos());
            }
        }
        prevTile = currTile;
    }

    for(auto& wp: waypoints) {
        static const Size<int> centerOffset{ TILE_SIZE / 2, TILE_SIZE / 2 };
        wp.AddOffset(centerOffset);
        DEBUG(StringFormat("Created Waypoint (%d, %d) -> (%d, %d)",
            wp.GetStart().x,
            wp.GetStart().y,
            wp.GetEnd().x,
            wp.GetEnd().y
        ));
    }
}

Size<double> Path::GetMoveOffset(const Point& pos) {
    return GetCurrentWaypoint(pos).GetMoveOffset(pos);
}

Waypoint& Path::GetCurrentWaypoint(const Point& pos) {
    INFO(StringFormat("Distance to wp: %d", waypoints.back().GetDistance(pos)));
    if(waypoints.back().GetDistance(pos) < 5) {
        waypoints.pop_back();
    }
    return waypoints.back();
}

bool Path::ReachedDestination() const {
    return waypoints.empty();
}

}
