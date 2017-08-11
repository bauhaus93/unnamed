#include "Atlas.h"

namespace unnamed::atlas {

static Size CalculateSize(const Size& exactFit, const Size& maxSize);

Atlas::Atlas(sdl::SDLWrapper& sdlWrapper, const Size& exactFit, const Size& maxSize):
    size { CalculateSize(exactFit, maxSize) },
    sprite { sdlWrapper, size },
    root { std::make_unique<Node>(Rect{ 0, 0, size.x, size.y })} {

    SetAsRenderTarget();
    sdlWrapper.UseNoBlending();
    sdlWrapper.DrawFillRect(Rect{ 0, 0, size.x, size.y }, Color{ 0xFF, 0xFF, 0xFF, 0});
    sdlWrapper.UseAlphaBlending();
    sdlWrapper.ClearRenderTarget();
    INFO(StringFormat("Created atlas with size %d/%d, fitting elements of size %d/%d",
        size.x,
        size.y,
        exactFit.x,
        exactFit.y));

}

Element& Atlas::AddElement(const Size& size) {
    return root->AddElement(size, sprite);
}

void Atlas::Draw(const Rect& rect) const {
    sprite.Draw(Rect{ 0, 0, size.x, size.y }, rect);
}

void Atlas::SetAsRenderTarget() {
    sprite.SetAsRenderTarget();
}

Size CalculateSize(const Size& exactFit, const Size& maxSize) {
    if (exactFit.x > maxSize.x || exactFit.y > maxSize.y) {
        throw exception::GameException("CalculateSize", "Max atlas size must be at least as big as demanded exact fit");
    }

    Size currSize { exactFit.x, exactFit.y };

    while (currSize.x < maxSize.x && currSize.y < maxSize.y) {
        currSize.x *= 2;
        currSize.y *= 2;
    }
    return currSize;
}

}
