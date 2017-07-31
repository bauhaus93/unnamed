#include "SDLWrapper.h"

SDLWrapper::SDLWrapper() {
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
}

SDLWrapper::~SDLWrapper() {
    SDL_Quit();
    INFO("SDL closed");
}
