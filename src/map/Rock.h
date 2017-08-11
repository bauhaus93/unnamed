#pragma once

#include "common/Rect.h"
#include "common/Point.h"
#include "atlas/Element.h"

namespace unnamed::map {

class Rock {

    atlas::Element&    sprite;

public:
    explicit                Rock(atlas::Element& sprite_);

    atlas::Element&      GetSprite() const;

};

}
