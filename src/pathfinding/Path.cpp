#include "Path.h"


Path::Path(PathNode* dest) {
    for(PathNode* curr = dest; curr != nullptr; curr = curr->GetPredecessor()) {
        waypoints.push_back(curr->GetTile());
    }
}

Tile* Path::GetNextTile() {
    if (!waypoints.empty()) {
        Tile* t = waypoints.back();
        waypoints.pop_back();
        return t;
    }
    return nullptr;
}
