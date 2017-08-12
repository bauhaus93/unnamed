#include "Atlas.h"

namespace unnamed::atlas {

Size<int> CalculateSize(const Size<int>& exactFit, const Size<int>& maxSize) {
    if (exactFit.x > maxSize.x || exactFit.y > maxSize.y) {
        throw exception::GameException("CalculateSize<int>", "Max atlas size must be at least as big as demanded exact fit");
    }

    Size<int> currSize { exactFit.x, exactFit.y };

    while (currSize.x < maxSize.x && currSize.y < maxSize.y) {
        currSize.x *= 2;
        currSize.y *= 2;
    }
    return currSize;
}


Atlas::Atlas(sdl::Wrapper& sdlWrapper, const Size<int>& exactFit, const Size<int>& maxSize):
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

std::shared_ptr<Element> Atlas::AddElement(const Size<int>& elementSize) {
    return root->AddElement(elementSize, sprite);
}

void Atlas::Draw(const Rect& rect) const {
    sprite.Draw(Rect{ 0, 0, size.x, size.y }, rect);
}

void Atlas::SetAsRenderTarget() {
    sprite.SetAsRenderTarget();
}



}
