#include <iostream>

#include "logger/StdLogger.h"
#include "sdl_wrapper/SDLWrapper.h"
#include "event/Event.h"

using namespace std;

int main(int argc, char** argv) {
    SDLWrapper sdlWrapper { "Unnamed", 1024, 768 };

    sdlWrapper.StartTimers();

    sdlWrapper.RenderPrepare();
    sdlWrapper.RenderPresent();

    while (true) {
        Event event = sdlWrapper.WaitEvent();
        switch (event.GetType()) {
        case EventType::RENDER:
            INFO("RENDER!");
            break;
        case EventType::UPDATE:
            INFO("UPDATE!");
            break;
        case EventType::QUIT:
            INFO("Received quit event");
            return 0;
        default:
            WARN("Unknown event");
            break;
        }
    }



    return 0;
}
