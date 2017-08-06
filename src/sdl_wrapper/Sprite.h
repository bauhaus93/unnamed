#pragma once

#ifdef _WIN32
#include <SDL/SDL.h>
#endif
#ifdef __linux__
#include <SDL2/SDL.h>
#endif

#include "SDLWrapper.h"
#include "SDLException.h"
#include "Rect.h"

class Sprite {

    SDLWrapper&         sdlWrapper;
    SDL_Texture*        texture;


public:

                        Sprite(SDLWrapper& sdlWrapper_, int sizeX, int sizeY);


    void                SetAsRenderTarget();
    void                Draw(const Rect& srcRect, const Rect& destRect);

};
