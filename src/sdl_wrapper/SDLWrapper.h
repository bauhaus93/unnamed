#pragma once

#ifdef _WIN32
#include <SDL/SDL.h>
#endif
#ifdef __linux__
#include <SDL2/SDL.h>
#endif

#include <string>

#include "logger/StdLogger.h"
#include "exception/GameException.h"
#include "event/Event.h"
#include "SDLException.h"


class SDLWrapper {

    SDL_Window*     window;
    SDL_Renderer*   renderer;
    SDL_TimerID     timerRender;
    SDL_TimerID     timerUpdate;
    Uint32          eventTypeRender;
    Uint32          eventTypeUpdate;

public:

                        SDLWrapper(const std::string& windowTitle, int windowSizeX, int windowSizeY);
                        ~SDLWrapper();

        void            RenderPrepare();
        void            RenderPresent();
        void            StartTimers();
        void            StopTimers();
        Event           WaitEvent();

        SDL_Renderer*   GetRenderer() const;

};

Uint32 RenderCallback(Uint32 delay, void* params);
Uint32 UpdateCallback(Uint32 delay, void* params);
