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
#include "frequency_handler/FrequencyHandler.h"

namespace unnamed::sdl {

struct CallbackData {
    Uint32 eventType;
    const freq::FrequencyHandler& handler;
    SDL_TimerID timerId;
    CallbackData(Uint32 eventType_, const freq::FrequencyHandler& handler_, SDL_TimerID timerId_):
        eventType { eventType_ },
        handler { handler_ },
        timerId { timerId_ } {
    }
};


class Wrapper {

    SDL_Window*                      window;
    SDL_Renderer*                    renderer;
    std::unique_ptr<CallbackData>    dataRender;
    std::unique_ptr<CallbackData>    dataUpdate;

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


        void                    StartTimers(const freq::FrequencyHandler& fpsHandler, const freq::FrequencyHandler& upsHandler);
        void                    StopTimers();
        std::unique_ptr<event::Event>  WaitEvent();

        SDL_Renderer*           GetRenderer() const;

};

}
