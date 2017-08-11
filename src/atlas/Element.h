#pragma once

#include "common/Rect.h"
#include "sdl_wrapper/Sprite.h"

namespace unnamed::atlas {

class Element {

    Rect                rect;
    sdl::Sprite&        atlasSprite;    //TODO make const again (conflicts with MarkRed herper method)


public:

                    Element(const Rect& rect, sdl::Sprite& atlasSprite_);

    void            SetAsRenderTarget();

    void            Draw(const Point& pos) const;
    Rect            GetRect() const;
    void            MarkRed();


};

}
