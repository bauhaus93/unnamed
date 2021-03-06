#pragma once

#include <SDL2/SDL.h>

#include "Wrapper.h"
#include "SDLException.h"
#include "common/Rect.h"
#include "common/Size.h"

namespace unnamed::sdl {

class Sprite {

    Wrapper&            sdlWrapper;
    SDL_Texture*        texture;


public:

                        Sprite(Wrapper& sdlWrapper_, const Size<int>& size);


    void                SetAsRenderTarget();
    void                Draw(const Rect& srcRect, const Rect& destRect) const;
    void                MarkRed(const Rect& rect);

};

}
