#pragma once

#include <vector>

#include "atlas/Atlas.h"
#include "atlas/Element.h"
#include "sdl_wrapper/Wrapper.h"
#include "exception/GameException.h"
#include "map/tile/Tile.h"
#include "Unit.h"

namespace unnamed::unit {

class UnitManager {

    atlas::Atlas&                                   atlas;
    sdl::Wrapper&                                   sdlWrapper;
    std::vector<Unit>                               units;
    std::vector<std::shared_ptr<atlas::Element>>    sprites;

    std::vector<Unit>::iterator                     currIter;

public:

                            UnitManager(atlas::Atlas& atlas_, sdl::Wrapper& sdlWrapper_);
    void                    CreateTestUnit(map::Tile* startTile);

    void                    ResetIteration();
    Unit&                   GetNextUnit();
    bool                    HasNextUnit() const;

    int                     GetUnitCount() const;

    void                    DrawUnits(const Rect& drawRect, const Point& cameraPos);


};



}
