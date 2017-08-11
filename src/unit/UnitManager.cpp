#include "UnitManager.h"


namespace unnamed::unit {

UnitManager::UnitManager(atlas::Atlas& atlas_, sdl::Wrapper& sdlWrapper_):
    atlas { atlas_ },
    sdlWrapper { sdlWrapper_ },
    units { },
    sprites {},
    currIter { units.end() } {

    Size unitSize { 50, 50 };
    auto basicSprite = atlas.AddElement(unitSize);

    basicSprite->SetAsRenderTarget();
    Rect spriteRect = basicSprite->GetRect();
    sdlWrapper.DrawFilledCircle(Point { spriteRect.x + 25, spriteRect.y + 24 }, 24, Color { 0xFF, 0, 0, 0xFF });
    sdlWrapper.ClearRenderTarget();
    sprites.push_back(basicSprite);

}

void UnitManager::CreateTestUnit(map::Tile* startTile) {
    units.emplace_back(startTile, sprites.back());
}

void UnitManager::ResetIteration() {
    currIter = units.begin();
}

Unit& UnitManager:: GetNextUnit() {
    if (!HasNextUnit()) {
        throw exception::GameException("UnitManager::GetNextUnit", "No next unit available");
    }
    return *currIter++;
}

bool UnitManager::HasNextUnit() const {
    return currIter != units.end();
}

int UnitManager::GetUnitCount() const {
    return units.size();
}

void UnitManager::DrawUnits(const Rect& rect, const Point& cameraPos) {

    for (auto& unit: units) {
        Point unitPos = unit.GetPos();
        if (unitPos.x >= cameraPos.x &&
            unitPos.y >= cameraPos.y &&
            unitPos.x < cameraPos.x + rect.w &&
            unitPos.y < cameraPos.y + rect.h) {
            unit.Draw(cameraPos, Point{ rect.x, rect.y });
        }
    }
}

}
