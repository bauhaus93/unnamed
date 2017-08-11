#pragma once

#include "map/Tile.h"

class PathNode {

    Tile*       tile;
    PathNode*   pred;
    int         gScore;
    int         fScore;


public:
                PathNode(Tile* tile_, PathNode* pred_, int gScore_, int fScore_);
    Tile*       GetTile() const;
    PathNode*   GetPredecessor() const;
    int         GetGScore() const;
    int         GetFScore() const;

    void        SetPredecessor(PathNode* pred_);
    void        SetGScore(int gScore_);
    void        SetFScore(int fScore_);

};

bool operator<(const PathNode& a, const PathNode& b);
bool PathOrder(const PathNode* a, const PathNode* b);
bool operator==(const PathNode& a, const PathNode& b);
