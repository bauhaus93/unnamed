#include "Game.h"


Game::Game(const Size& windowSize):
    sdlWrapper { "unnamed", windowSize },
    atlas { sdlWrapper, Size{ 500, 500 }, 6 } {

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
    static Size size { 7, 7 };

    sdlWrapper.SetDrawColor(Color { 0xFF, 0xFF, 0, 0xFF });
    atlas.SetAsRenderTarget();
    try {
        auto e = atlas.AddElement(size);
        sdlWrapper.DrawRect(e.GetRect());
        //size.x += 10;
        //size.y += 10;
    }
    catch (const SubTreeFullException& e) {
        INFO("SUBTREE full");
    }
    sdlWrapper.ClearRenderTarget();
}
