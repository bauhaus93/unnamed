#include "Game.h"


Game::Game(int windowSizeX, int windowSizeY):
    sdlWrapper { "unnamed", windowSizeX, windowSizeY } {

}

void Game::Loop() {
    bool quit = false;

    sdlWrapper.StartTimers();

    while (!quit) {
        Event event = sdlWrapper.WaitEvent();
        switch (event.GetType()) {
        case EventType::RENDER:
            Render();
            break;
        case EventType::UPDATE:
            Update();
            break;
        case EventType::QUIT:
            INFO("Received quit event");
            quit = true;
            break;
        default:
            WARN("Unknown event");
            break;
        }
    }

    sdlWrapper.StopTimers();
}

void Game::Render() {
    sdlWrapper.RenderPrepare();
    sdlWrapper.RenderPresent();
}

void Game::Update() {
}
