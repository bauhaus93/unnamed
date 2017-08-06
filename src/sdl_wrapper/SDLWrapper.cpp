#include "SDLWrapper.h"

SDLWrapper::SDLWrapper(const std::string& windowTitle, int windowSizeX, int windowSizeY):
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
    char msg[50];

    snprintf(msg, 50, "Compiled with SDL %d.%d.%d", compiled.major,
                                                    compiled.minor,
                                                    compiled.patch);
    INFO(msg);

    snprintf(msg, 50, "Linked against SDL %d.%d.%d",    compiled.major,
                                                        compiled.minor,
                                                        compiled.patch);
    INFO(msg);
    if (compiled.major != linked.major ||
        compiled.minor != linked.minor ||
        compiled.patch != linked.patch) {
            WARN("SDL compiled/linked versions do not match");
    }

    window = SDL_CreateWindow(  windowTitle.c_str(),
                                SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED,
                                windowSizeX,
                                windowSizeY,
                                SDL_WINDOW_OPENGL);

    if (window == nullptr) {
        throw SDLException("SDL_CreateWindow");
    }
    INFO("Created window");

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

void SDLWrapper::RenderPrepare() {
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(renderer);
}

void SDLWrapper::RenderPresent() {
    SDL_RenderPresent(renderer);
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

    timerUpdate = SDL_AddTimer(250, UpdateCallback, (void*)&eventTypeUpdate);
    if (timerUpdate == 0) {
        throw SDLException("SDL_AddTimer");
    }
    INFO("Started update timer");

    timerRender = SDL_AddTimer(250, RenderCallback, (void*)&eventTypeRender);
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
