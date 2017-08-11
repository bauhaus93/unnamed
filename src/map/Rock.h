#pragma once

#include "common/Rect.h"
#include "common/Point.h"
#include "atlas/AtlasElement.h"

namespace unnamed::map {

class Rock {

    atlas::AtlasElement&    sprite;

public:
    explicit                Rock(atlas::AtlasElement& sprite_);

    atlas::AtlasElement&      GetSprite() const;

};

}
