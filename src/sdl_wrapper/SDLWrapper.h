#pragma once

#ifdef _WIN32
#include <SDL/SDL.h>
#endif
#ifdef __linux__
#include <SDL2/SDL.h>
#endif

#include <string>
#include <memory>

#include "logger/StdLogger.h"
#include "exception/GameException.h"
#include "event/Event.h"
#include "event/EventKeyDown.h"
#include "SDLException.h"
#include "common/Color.h"
#include "common/Point.h"
#include "common/Size.h"
#include "common/Rect.h"
#include "common/StringFormat.h"



class SDLWrapper {

    SDL_Window*     window;
    SDL_Renderer*   renderer;
    SDL_TimerID     timerRender;
    SDL_TimerID     timerUpdate;
    Uint32          eventTypeRender;
    Uint32          eventTypeUpdate;

public:

                                SDLWrapper(const std::string& windowTitle, const Size& windowSize);
                                ~SDLWrapper();

        void                    ClearScene();
        void                    ShowScene();
        void                    SetDrawColor(const Color& color);
        void                    SetWindowTitle(const std::string& title);
        void                    ClearRenderTarget();
        void                    DrawLine(const Point& start, const Point& stop);
        void                    DrawRect(const Rect& rect);
        void                    DrawFillRect(const Rect& rect);


        void                    StartTimers();
        void                    StopTimers();
        std::unique_ptr<Event>  WaitEvent();

        SDL_Renderer*           GetRenderer() const;

};
