#pragma once

#include <cmath>

#include "common/Point.h"
#include "common/Size.h"

namespace unnamed::map {

class Waypoint {

    Point           start;
    Point           end;
    bool            reachedStart;

public:

                    Waypoint();
    void            SetStart(const Point& start_);
    void            SetEnd(const Point& end_);
    void            AddOffset(const Size<int>& offset);
    void            SetReachedStart();
    bool            ReachedStart() const;
    Point           GetStart() const;
    Point           GetEnd() const;
    Point           GetTarget() const;
    Size<double>    GetMoveOffset(const Point& pos) const;
    int             GetDistance(const Point& pos) const;
};



}
