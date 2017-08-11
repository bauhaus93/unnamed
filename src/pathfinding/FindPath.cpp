#include "FindPath.h"

int DistanceHeuristic(Tile* curr, Tile* dest);
std::vector<PathNode*> ReconstructPath(PathNode* dest);
PathNode* GetNodeFromList(Tile* tile, std::vector<PathNode*>& list);

void FindPath(Tile* src, Tile* dest) {
    std::priority_queue<PathNode*> openSet;
    std::vector<PathNode*> closedSet;

    openSet.push(new PathNode(src, nullptr, 0, DistanceHeuristic(src, dest)));

    while (!openSet.empty()) {
        PathNode* currNode = openSet.top();
        INFO(StringFormat("top node g() = %d, f() = %d", currNode->GetGScore(), currNode->GetFScore()));

        openSet.pop();
        closedSet.push_back(currNode);

        if (currNode->GetTile() == dest) {
            INFO(StringFormat("found path!"));
            auto path = ReconstructPath(currNode);
            while(!path.empty()) {
                INFO(StringFormat("path: (%d/%d)", path.back()->GetTile()->GetPos()));
                delete path.back();
                path.pop_back();
            }
            break;
        }

        for(int i = 0; i < 4; i++) {
            static const Direction neighbours[] = { Direction::NORTH,
                                                    Direction::EAST,
                                                    Direction::SOUTH,
                                                    Direction::WEST };
            Tile* currNB = currNode->GetTile()->GetNeighbour(neighbours[i]);
            if (GetTileFromList(currNB, closedSet) != nullptr)
                continue;

            if (TileInList(currNB, openSet)) {
                openSet.push(new PathNode(currNB, currNode, currNode->GetGScore(), DistanceHeuristic(currNB, dest)));
            }

        }

    }
}

int DistanceHeuristic(Tile* curr, Tile* dest) {
    Point a = curr->GetPos();
    Point b = dest->GetPos();

    int diffX = a.x - b.x;
    int diffY = a.y - b.y;
    diffX *= diffX;
    diffY *= diffY;
    return sqrt(diffX + diffY);
}

std::vector<PathNode*> ReconstructPath(PathNode* dest) {
    std::vector<PathNode*> path;
    for(PathNode* curr = dest; curr != nullptr; curr = curr->GetPredecessor()) {
        path.push_back(curr);
    }
    return path;
}

PathNode* GetNodeFromList(Tile* tile, std::vector<PathNode*>& list) {
    for(auto& e: list) {
        if (e->GetTile() == tile)
            return e;
    }
    return nullptr;
}
