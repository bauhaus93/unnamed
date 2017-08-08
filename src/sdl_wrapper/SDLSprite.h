#pragma once

#ifdef _WIN32
#include <SDL/SDL.h>
#endif
#ifdef __linux__
#include <SDL2/SDL.h>
#endif

#include "SDLWrapper.h"
#include "SDLException.h"
#include "common/Rect.h"
#include "common/Size.h"

class SDLSprite {

    SDLWrapper&         sdlWrapper;
    SDL_Texture*        texture;


public:

                        SDLSprite(SDLWrapper& sdlWrapper_, const Size& size);


    void                SetAsRenderTarget();
    void                Draw(const Rect& srcRect, const Rect& destRect) const;

};
