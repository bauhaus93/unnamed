#pragma once

#include <SDL2/SDL.h>

#include <SDL2/SDL2_gfxPrimitives.h>

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

namespace unnamed::sdl {

class Wrapper {

    SDL_Window*     window;
    SDL_Renderer*   renderer;
    SDL_TimerID     timerRender;
    SDL_TimerID     timerUpdate;
    Uint32          eventTypeRender;
    Uint32          eventTypeUpdate;

public:

                                Wrapper(const std::string& windowTitle, const Size<int>& windowSize);
                                ~Wrapper();

        void                    ClearScene();
        void                    ShowScene();
        void                    SetDrawColor(const Color& color);
        void                    SetWindowTitle(const std::string& title);
        void                    ClearRenderTarget();
        void                    UseAlphaBlending();
        void                    UseNoBlending();

        void                    DrawLine(const Point& start, const Point& stop, const Color& color);
        void                    DrawRect(const Rect& rect, const Color& color);
        void                    DrawFillRect(const Rect& rect, const Color& color);
        void                    DrawRoundedFillRect(const Rect& rect, int radius, const Color& color);
        void                    DrawPoint(const Point& point, const Color& color);
        void                    DrawFilledCircle(const Point& origin, int radius, const Color& color);


        void                    StartTimers();
        void                    StopTimers();
        std::unique_ptr<event::Event>  WaitEvent();

        SDL_Renderer*           GetRenderer() const;

};

}
