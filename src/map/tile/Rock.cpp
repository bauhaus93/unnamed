#include "Rock.h"

namespace unnamed::map {

Rock::Rock(atlas::Element& sprite_):
    sprite { sprite_ } {

}

atlas::Element& Rock::GetSprite() const{
    return sprite;
}

}
