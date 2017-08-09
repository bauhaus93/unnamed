#include "Game.h"


Game::Game(const Size& windowSize):
    sdlWrapper { "unnamed", windowSize },
    rng {},
    atlas { sdlWrapper, Size{ 40, 40 }, Size{ 1000, 1000 } } {

    INFO(StringFormat("Game seed: %u", rng.GetSeed()));
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

    sdlWrapper.SetDrawColor(Color { 0, 0, 0, 0xFF });
    sdlWrapper.ClearScene();
    atlas.Draw(Rect { 0, 0, 500, 500 });
    sdlWrapper.SetDrawColor(Color { 0xFF, 0, 0, 0xFF });
    sdlWrapper.DrawRect(Rect { 0, 0, 500, 500 });
    sdlWrapper.ShowScene();
}

void Game::Update() {

    sdlWrapper.SetDrawColor(Color { rng.Random(0, 256), rng.Random(0, 256), rng.Random(0, 256), 0xFF });
    atlas.SetAsRenderTarget();
    try {
        //Size size { rng.Random(15, 20), rng.Random(15, 20) };
        Size size { 40, 40 };
        auto e = atlas.AddElement(size);
        sdlWrapper.DrawFillRect(e.GetRect());
    }
    catch (const NoAtlasSpaceException&) {
        INFO("Atlas is full");
    }
    sdlWrapper.ClearRenderTarget();
}
