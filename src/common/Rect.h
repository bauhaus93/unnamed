#pragma once

#include "Point.h"

namespace unnamed {

struct Rect {
    int x;
    int y;
    int w;
    int h;
};

bool PointInRectangle(const Point& p, const Rect& rect);

}
