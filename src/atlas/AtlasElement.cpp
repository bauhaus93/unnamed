#include "AtlasElement.h"


AtlasElement::AtlasElement(const Rect& rect_, SDLSprite& atlasSprite_):
    rect { rect_ },
    atlasSprite { atlasSprite_ } {


}

void AtlasElement::Draw(const Point& pos) const {
    atlasSprite.Draw(rect, Rect{ pos.x, pos.y, rect.w, rect.h });
}

Rect AtlasElement::GetRect() const {
    return rect;
}

void AtlasElement::MarkRed() {
    atlasSprite.MarkRed(rect);
}
