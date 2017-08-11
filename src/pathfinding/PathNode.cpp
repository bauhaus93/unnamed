#include "PathNode.h"

PathNode::PathNode(Tile* tile_, PathNode* pred_, int gScore_, int fScore_):
    tile { tile_ },
    pred { pred_ },
    gScore { gScore_ },
    fScore { fScore_ } {
}

Tile* PathNode::GetTile() const {
    return tile;
}

PathNode* PathNode::GetPredecessor() const {
    return pred;
}

int PathNode::GetGScore() const {
    return gScore;
}

int PathNode::GetFScore() const {
    return fScore;
}

bool operator==(const PathNode& a, const PathNode& b) {
    return a.GetTile() == b.GetTile();
}
