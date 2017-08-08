#pragma once

#include <memory>

#include "sdl_wrapper/SDLWrapper.h"
#include "sdl_wrapper/SDLSprite.h"
#include "common/Size.h"
#include "common/Rect.h"
#include "common/Point.h"
#include "Node.h"
#include "AtlasElement.h"

class Atlas {

    Size                    size;
    SDLSprite               sprite;
    std::unique_ptr<Node>   root;



public:

                            Atlas(SDLWrapper& sdlWrapper, const Size& size, int depth);
        AtlasElement&       AddElement(const Size& size);
        void                Draw(const Rect& rect) const;
        void                SetAsRenderTarget();

};
