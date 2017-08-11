#include "PathNode.h"

namespace unnamed::map {

PathNode::PathNode(map::Tile* tile_, PathNode* pred_, int gScore_, int fScore_):
    tile { tile_ },
    pred { pred_ },
    gScore { gScore_ },
    fScore { fScore_ } {
}

map::Tile* PathNode::GetTile() const {
    return tile;
}

PathNode* PathNode::GetPredecessor() const {
    return pred;
}

void PathNode::SetPredecessor(PathNode* pred_) {
    pred = pred_;
}

int PathNode::GetGScore() const {
    return gScore;
}

void PathNode::SetGScore(int gScore_) {
    gScore = gScore_;
}

int PathNode::GetFScore() const {
    return fScore;
}

void PathNode::SetFScore(int fScore_) {
    fScore = fScore_;
}

bool operator<(const PathNode& a, const PathNode& b) {
    return a.GetFScore() > b.GetFScore();
}

bool PathOrder(const PathNode* a, const PathNode* b) {
    return a->GetFScore() > b->GetFScore();
}

bool operator==(const PathNode& a, const PathNode& b) {
    return a.GetTile() == b.GetTile();
}

}
