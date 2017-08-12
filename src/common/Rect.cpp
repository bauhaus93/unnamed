#include "Rect.h"


namespace unnamed {

bool PointInRectangle(const Point& p, const Rect& rect) {
    return  p.x >= rect.x &&
            p.y >= rect.y &&
            p.x < rect.x + rect.w &&
            p.y < rect.y + rect.h;
}


}
