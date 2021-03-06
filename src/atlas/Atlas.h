#pragma once

#include <memory>

#include "sdl_wrapper/Wrapper.h"
#include "sdl_wrapper/Sprite.h"
#include "common/Size.h"
#include "common/Rect.h"
#include "common/Point.h"
#include "exception/GameException.h"
#include "Node.h"
#include "Element.h"

namespace unnamed::atlas {

class Atlas {

    Size<int>               size;
    sdl::Sprite             sprite;
    std::unique_ptr<Node>   root;



public:

                                    Atlas(sdl::Wrapper& sdlWrapper, const Size<int>& exactFit, const Size<int>& maxSize);
        std::shared_ptr<Element>    AddElement(const Size<int>& elementSize);
        void                        Draw(const Rect& rect) const;
        void                        SetAsRenderTarget();

};

}
