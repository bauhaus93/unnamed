#include "Waypoint.h"


namespace unnamed::map {


Size<double> CalculateMoveOffset(const Point& src, const Point& dest) {
    if (src.x != dest.x || src.y != dest.y) {
        Size<double> offset { static_cast<double>(dest.x - src.x),
                              static_cast<double>(dest.y - src.y) };
        double len = sqrt(offset.x * offset.x + offset.y * offset.y);
        offset.x /= len;
        offset.y /= len;
        return offset;
    }
    return Size<double> { 0.0, 0.0 };
}


Waypoint::Waypoint():
    start { 0, 0 },
    end { 0, 0 },
    reachedStart { false } {

}

void Waypoint::SetStart(const Point& start_) {
    start = start_;
}

void Waypoint::SetEnd(const Point& end_) {
    end = end_;
}

void Waypoint::AddOffset(const Size<int>& offset) {
    start.x += offset.x;
    start.y += offset.y;
    end.x += offset.x;
    end.y += offset.y;
}

void Waypoint::SetReachedStart() {
    reachedStart = true;
}

bool Waypoint::ReachedStart() const {
    return reachedStart;
}

Point Waypoint::GetStart() const {
    return start;
}

Point Waypoint::GetEnd() const {
    return end;
}

Point Waypoint::GetTarget() const {
    return ReachedStart() ? GetEnd() : GetStart();
}

int Waypoint::GetDistance(const Point& pos) const {
    return Distance(pos, GetTarget());
}

Size<double> Waypoint::GetMoveOffset(const Point& pos) const {
    return CalculateMoveOffset(pos, GetTarget());
}


}
