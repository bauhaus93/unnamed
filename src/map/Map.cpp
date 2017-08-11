#include "Map.h"

namespace unnamed::map {

Map::Map(const Size& size_, LandscapeGenerator& landscapeGenerator_):
    size { size_ },
    landscapeGenerator { landscapeGenerator_ },
    root { landscapeGenerator.Generate(Rect{ 0, 0, size.x, size.y }) },
    camera { root } {
}

Map::~Map() {
    INFO("Destroying map");
    std::vector<Tile*> tiles;
    for (Tile* currRow = root; currRow != nullptr; currRow = currRow->GetNeighbour(Direction::SOUTH)) {
        for (Tile* currTile = currRow; currTile != nullptr; currTile = currTile->GetNeighbour(Direction::EAST)) {
            tiles.push_back(currTile);
        }
    }
    INFO(StringFormat("Freeing %d tiles", tiles.size()));

    if (tiles.size() != static_cast<size_t>(size.x * size.y)) {
        ERROR(StringFormat("Map should contain %d tiles, but %d are freed",
            size.x * size.y,
            tiles.size()));
    }

    while (!tiles.empty()){
        delete tiles.back();
        tiles.pop_back();
    }
}

void Map::Draw(const Rect& destRect) {
    Tile* currRow = camera;
    Tile* nextRow = camera->GetNeighbour(Direction::SOUTH);
    Point cameraPos = camera->GetPos();
    Point destOffset = Point{ destRect.x, destRect. y };

    while (currRow != nullptr && currRow->GetPos().y < cameraPos.y + destRect.h) {

        for(Tile* currTile = currRow;
            currTile != nullptr &&
            currTile->GetPos().x < cameraPos.x + destRect.w;
            currTile = currTile->GetNeighbour(Direction::EAST)) {
            currTile->Draw(cameraPos, destOffset);
        }
        currRow = nextRow;
        if (currRow != nullptr) {
            nextRow = currRow->GetNeighbour(Direction::SOUTH);
        }
    }
}

void Map::MoveCamera(Direction dir) {
    Tile* nb = camera->GetNeighbour(dir);
    if (nb != nullptr) {
        camera = nb;
    }
}

}
