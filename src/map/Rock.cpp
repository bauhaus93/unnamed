#include "Rock.h"

namespace unnamed::map {

Rock::Rock(atlas::AtlasElement& sprite_):
    sprite { sprite_ } {

}

atlas::AtlasElement& Rock::GetSprite() const{
    return sprite;
}

}
