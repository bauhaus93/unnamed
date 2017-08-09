#pragma once

#include "common/Rect.h"
#include "common/Point.h"
#include "atlas/AtlasElement.h"

class Rock {

    AtlasElement&       sprite;

public:
    explicit            Rock(AtlasElement& sprite_);

    AtlasElement&       GetSprite() const;

};
