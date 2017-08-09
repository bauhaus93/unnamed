#include "SDLWrapper.h"

SDLWrapper::SDLWrapper(const std::string& windowTitle, const Size& windowSize):
    window { nullptr },
    renderer { nullptr },
    timerRender { 0 },
    timerUpdate { 0 },
    eventTypeRender { (Uint32)-1 },
    eventTypeUpdate { (Uint32)-1 } {

    INFO("Initializing SDL2...");

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER) != 0) {
        throw SDLException("SDL_Init");
    }
    INFO("SDL initialized");

    SDL_version compiled;
    SDL_version linked;

    SDL_VERSION(&compiled);
    SDL_GetVersion(&linked);

    INFO(StringFormat("Compiled with SDL %d.%d.%d", compiled.major,
                                                    compiled.minor,
                                                    compiled.patch));


    INFO(StringFormat("Linked against SDL %d.%d.%d",    linked.major,
                                                        linked.minor,
                                                        linked.patch));

    if (compiled.major != linked.major ||
        compiled.minor != linked.minor ||
        compiled.patch != linked.patch) {
            WARN(StringFormat("SDL compiled/linked versions do not match: %d.%d.%d/%d.%d.%d",
                compiled.major,
                compiled.minor,
                compiled.patch,
                linked.major,
                linked.minor,
                linked.patch));
    }

    window = SDL_CreateWindow(  windowTitle.c_str(),
                                SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED,
                                windowSize.x,
                                windowSize.y,
                                SDL_WINDOW_OPENGL);

    if (window == nullptr) {
        throw SDLException("SDL_CreateWindow");
    }
    INFO(StringFormat("Created window %dx%d", windowSize.x, windowSize.y));

    renderer = SDL_CreateRenderer(  window,
                                    -1,
                                    SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);

    if (renderer == nullptr) {
        throw SDLException("SDL_CreateRenderer");
    }
    INFO("Created renderer");

}

SDLWrapper::~SDLWrapper() {

    StopTimers();

    if (renderer != nullptr) {
        SDL_DestroyRenderer(renderer);
        INFO("Destroyed renderer");
    }

    if (window != nullptr) {
        SDL_DestroyWindow(window);
        INFO("Destroyed window");
    }
    SDL_Quit();
    INFO("SDL quit");
}

void SDLWrapper::ClearScene() {
    SDL_RenderClear(renderer);
}

void SDLWrapper::ShowScene() {
    SDL_RenderPresent(renderer);
}

void SDLWrapper::ClearRenderTarget(){
    if (SDL_SetRenderTarget(renderer, nullptr) == -1)
        throw SDLException("SDL_SetRenderTarget");
}

void SDLWrapper::SetDrawColor(const Color& color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
}

void SDLWrapper::SetWindowTitle(const std::string& title){
	SDL_SetWindowTitle(window, title.c_str());
}

void SDLWrapper::DrawLine(const Point& start, const Point& stop) {
    if (SDL_RenderDrawLine(renderer, start.x, start.y, stop.x, stop.y) < 0) {
        throw SDLException("SDL_DrawLine");
    }
}

void SDLWrapper::DrawRect(const Rect& rect) {
    SDL_Rect sdlRect { rect.x, rect.y, rect.w, rect.h };
    if (SDL_RenderDrawRect(renderer, &sdlRect) < 0) {
        throw SDLException("SDL_DrawRect");
    }
}

void SDLWrapper::DrawFillRect(const Rect& rect) {
    SDL_Rect sdlRect { rect.x, rect.y, rect.w, rect.h };
    if (SDL_RenderFillRect(renderer, &sdlRect) < 0) {
        throw SDLException("SDL_DrawRect");
    }
}

void SDLWrapper::StartTimers() {

    eventTypeUpdate = SDL_RegisterEvents(2);
    if (eventTypeUpdate == (Uint32)-1) {
        throw SDLException("SDL_RegisterEvents");
    }

    eventTypeRender = eventTypeUpdate++;
    if (eventTypeRender == (Uint32)-1) {
        throw SDLException("SDL_RegisterEvents");
    }

    timerUpdate = SDL_AddTimer(10, UpdateCallback, (void*)&eventTypeUpdate);
    if (timerUpdate == 0) {
        throw SDLException("SDL_AddTimer");
    }
    INFO("Started update timer");

    timerRender = SDL_AddTimer(50, RenderCallback, (void*)&eventTypeRender);
    if (timerRender == 0) {
        throw SDLException("SDL_AddTimer");
    }
    INFO("Started render timer");
}

void SDLWrapper::StopTimers() {
    if (timerRender != 0) {
        SDL_RemoveTimer(timerRender);
        timerRender = 0;
        INFO("Removed render timer");
    }

    if (timerUpdate != 0) {
        SDL_RemoveTimer(timerUpdate);
        timerUpdate = 0;
        INFO("Removed update timer");
    }
}

Event SDLWrapper::WaitEvent() {
    SDL_Event sdlEvent;
    Event event{};

    while (event.GetType() == EventType::NONE) {

        if (SDL_WaitEvent(&sdlEvent) == 0) {
            throw SDLException("SDL_WaitEvent");
        }
        if (sdlEvent.type == eventTypeRender)
            event.SetType(EventType::RENDER);
        else if (sdlEvent.type == eventTypeUpdate)
            event.SetType(EventType::UPDATE);
        else {
            switch (sdlEvent.type){
            case SDL_QUIT:
                event.SetType(EventType::QUIT);
                break;
            }
        }
    }

    return event;
}

SDL_Renderer* SDLWrapper::GetRenderer() const {
    return renderer;
}

Uint32 RenderCallback(Uint32 interval, void* param) {
    SDL_Event event;

    memset(&event, 0, sizeof(SDL_Event));
    event.type = *(Uint32*)param;
    SDL_PushEvent(&event);

    return interval;
}

Uint32 UpdateCallback(Uint32 interval, void* param) {
    SDL_Event event;

    memset(&event, 0, sizeof(SDL_Event));
    event.type = *(Uint32*)param;
    SDL_PushEvent(&event);

    return interval;
}
