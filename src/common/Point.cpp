#include "Point.h"


namespace unnamed {

int Distance(const Point& a, const Point& b) {
    int diffX = a.x - b.x;
    int diffY = a.y - b.y;
    diffX *= diffX;
    diffY *= diffY;
    return static_cast<int>(sqrt(diffX + diffY));
}

}
