#include "Game.h"

namespace unnamed {

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
        case event::EventType::RENDER:
            Render();
            break;
        case event::EventType::UPDATE:
            Update();
            break;
        case event::EventType::QUIT:
            INFO("Received quit event");
            quit = true;
            break;
        case event::EventType::KEY_DOWN:
            HandleKeyDown(static_cast<event::EventKeyDown&>(*event));
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

void Game::HandleKeyDown(event::EventKeyDown& event) {
    switch (event.GetKey()) {
    case event::Key::UP:       map.MoveCamera(map::Direction::NORTH);   break;
    case event::Key::DOWN:     map.MoveCamera(map::Direction::SOUTH);   break;
    case event::Key::LEFT:     map.MoveCamera(map::Direction::WEST);    break;
    case event::Key::RIGHT:    map.MoveCamera(map::Direction::EAST);    break;
    default:                   INFO("Unhandled key pressed");           break;
    }
}

}
