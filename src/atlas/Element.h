#pragma once

#include "common/Rect.h"
#include "sdl_wrapper/SDLSprite.h"

namespace unnamed::atlas {

class Element {

    Rect                rect;
    sdl::SDLSprite&     atlasSprite;    //TODO make const again (conflicts with MarkRed herper method)


public:

                    Element(const Rect& rect, sdl::SDLSprite& atlasSprite_);

    void            Draw(const Point& pos) const;
    Rect            GetRect() const;
    void            MarkRed();


};

}
