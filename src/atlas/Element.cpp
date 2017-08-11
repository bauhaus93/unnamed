#include "Element.h"

namespace unnamed::atlas {

Element::Element(const Rect& rect_, sdl::Sprite& atlasSprite_):
    rect { rect_ },
    atlasSprite { atlasSprite_ } {
}

void Element::SetAsRenderTarget() {
    atlasSprite.SetAsRenderTarget();
}

void Element::Draw(const Point& pos) const {
    atlasSprite.Draw(rect, Rect{ pos.x, pos.y, rect.w, rect.h });
}

Rect Element::GetRect() const {
    return rect;
}

void Element::MarkRed() {
    atlasSprite.MarkRed(rect);
}

}
