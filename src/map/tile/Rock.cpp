#include "Rock.h"

namespace unnamed::map {

Rock::Rock(std::shared_ptr<atlas::Element> sprite_):
    sprite { sprite_ } {

}

std::shared_ptr<atlas::Element>& Rock::GetSprite(){
    return sprite;
}

}
