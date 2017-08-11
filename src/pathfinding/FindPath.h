#pragma once

#include <algorithm>
#include <vector>
#include <memory>

#include "map/Tile.h"
#include "logger/StdLogger.h"
#include "PathNode.h"
#include "Path.h"


std::unique_ptr<Path> FindPath(Tile* src, Tile* dest);
