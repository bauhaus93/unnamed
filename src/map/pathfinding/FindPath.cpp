#include "FindPath.h"

namespace unnamed::map {

int DistanceHeuristic(Tile* curr, map::Tile* dest);
PathNode* GetNodeFromList(Tile* tile, std::vector<PathNode*>& list);

std::unique_ptr<Path> FindPath(Tile* src, Tile* dest, int arrivalRadius) {
    std::vector<PathNode*> openSet;
    std::vector<PathNode*> closedSet;

    openSet.push_back(new PathNode(src, nullptr, 0, DistanceHeuristic(src, dest)));

    while (!openSet.empty()) {
        std::pop_heap(openSet.begin(), openSet.end(), PathOrder);
        PathNode* currNode = openSet.back();
        openSet.pop_back();

        //INFO(StringFormat("curr @ %d/%d", currNode->GetTile()->GetPos().x, currNode->GetTile()->GetPos().y));

        closedSet.push_back(currNode);
        //std::push_heap(closedSet.begin(), closedSet.end(), PathOrder);

        if (currNode->GetTile() == dest) {
            std::unique_ptr<Path> path = std::make_unique<Path>(currNode, arrivalRadius);
            while (!openSet.empty()) {
                delete openSet.back();
                openSet.pop_back();
            }
            while (!closedSet.empty()) {
                delete closedSet.back();
                closedSet.pop_back();
            }
            return path;
        }

        for(int i = 0; i < 4; i++) {
            static const Direction neighbours[] = { Direction::NORTH,
                                                    Direction::EAST,
                                                    Direction::SOUTH,
                                                    Direction::WEST };
            Tile* currNB = currNode->GetTile()->GetNeighbour(neighbours[i]);
            if (currNB == nullptr || !currNB->IsTraversable() || GetNodeFromList(currNB, closedSet) != nullptr)
                continue;

            PathNode* nbNode = GetNodeFromList(currNB, openSet);
            if (nbNode == nullptr) {
                nbNode = new PathNode(  currNB,
                                        currNode,
                                        currNode->GetGScore() + TILE_SIZE,
                                        currNode->GetGScore() + TILE_SIZE + DistanceHeuristic(currNB, dest));

                openSet.push_back(nbNode);
                std::push_heap(openSet.begin(), openSet.end(), PathOrder);
            }
            else {
                int gScore = currNode->GetGScore() + TILE_SIZE;
                if (gScore >= nbNode->GetGScore())
                    continue;
                nbNode->SetPredecessor(currNode);
                nbNode->SetGScore(gScore);
                nbNode->SetFScore(gScore + DistanceHeuristic(currNB, dest));
                std::make_heap(openSet.begin(), openSet.end(), PathOrder);
            }
        }
    }
    while (!closedSet.empty()) {
        delete closedSet.back();
        closedSet.pop_back();
    }
    return nullptr;
}

int DistanceHeuristic(Tile* curr, Tile* dest) {
    Point a = curr->GetPos();
    Point b = dest->GetPos();

    int diffX = a.x - b.x;
    int diffY = a.y - b.y;
    diffX *= diffX;
    diffY *= diffY;
    return static_cast<int>(sqrt(diffX + diffY));
}

PathNode* GetNodeFromList(Tile* tile, std::vector<PathNode*>& list) {
    for(auto& e: list) {
        if (e->GetTile() == tile)
            return e;
    }
    return nullptr;
}

}
