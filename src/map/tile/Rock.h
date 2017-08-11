#pragma once

#include <memory>

#include "common/Rect.h"
#include "common/Point.h"
#include "atlas/Element.h"

namespace unnamed::map {

class Rock {

    std::shared_ptr<atlas::Element>    sprite;

public:
    explicit                            Rock(std::shared_ptr<atlas::Element> sprite_);

    std::shared_ptr<atlas::Element>&    GetSprite();

};

}
