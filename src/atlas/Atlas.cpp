#include "Atlas.h"


Atlas::Atlas(SDLWrapper& sdlWrapper, const Size& size_, int depth):
    size { size_.x, size_.y },
    sprite { sdlWrapper, size },
    root { std::make_unique<Node>(Rect{ 0, 0, size.x, size.y })} {

    root->ExpandTree(depth);
}

AtlasElement& Atlas::AddElement(const Size& size) {
    return root->AddElement(size, sprite);
}

void Atlas::Draw(const Rect& rect) const {
    sprite.Draw(Rect{ 0, 0, size.x, size.y }, rect);
}

void Atlas::SetAsRenderTarget() {
    sprite.SetAsRenderTarget();
}
