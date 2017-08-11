#include "Game.h"


Game::Game(const Size& windowSize):
    sdlWrapper { "unnamed", windowSize },
    rng {},
    atlas { sdlWrapper, Size{ 50, 50 }, Size{ 4000, 4000 } },
    landscapeGenerator { sdlWrapper, atlas, rng.Random() },
    map { Size{ 40, 40 }, landscapeGenerator } {

    INFO(StringFormat("Game seed: %u", rng.GetSeed()));
}

void Game::Loop() {
    bool quit = false;

    sdlWrapper.StartTimers();

    while (!quit) {
        auto event = sdlWrapper.WaitEvent();
        switch (event->GetType()) {
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
        case EventType::KEY_DOWN:
            HandleKeyDown(static_cast<EventKeyDown&>(*event));
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
    map.Draw(Rect{ 0, 0, 1024, 768 });

    sdlWrapper.DrawFillRect(Rect{ 1024 - 210, 10, 200, 200 }, Color{  0, 0, 0, 0xFF });
    atlas.Draw(Rect{ 1024 - 210, 10, 200, 200 });
    sdlWrapper.DrawRect(Rect{ 1024 - 210, 10, 200, 200 }, Color{  0xFF, 0xFF, 0xFF, 0xFF });

    sdlWrapper.ShowScene();
}

void Game::Update() {
}

void Game::HandleKeyDown(EventKeyDown& event) {
    switch (event.GetKey()) {
    case Key::UP:       map.MoveCamera(Direction::NORTH);   break;
    case Key::DOWN:     map.MoveCamera(Direction::SOUTH);   break;
    case Key::LEFT:     map.MoveCamera(Direction::WEST);    break;
    case Key::RIGHT:    map.MoveCamera(Direction::EAST);    break;
    default:            INFO("Unhandled key pressed");      break;
    }
}
