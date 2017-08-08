#pragma once

#include "common/Rect.h"
#include "sdl_wrapper/SDLSprite.h"

class AtlasElement {

    Rect                rect;
    const SDLSprite&    atlasSprite;


public:

                    AtlasElement(const Rect& rect, SDLSprite& atlasSprite_);

    void            Draw(const Point& pos) const;
    Rect            GetRect() const;


};
