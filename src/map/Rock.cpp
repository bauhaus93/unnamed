#include "Rock.h"


Rock::Rock(AtlasElement& sprite_):
    sprite { sprite_ } {

}

AtlasElement& Rock::GetSprite() const{
    return sprite;
}
