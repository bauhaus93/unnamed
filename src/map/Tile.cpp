#include "Tile.h"

namespace unnamed::map {

Tile::Tile(const Point& pos, atlas::AtlasElement& sprite_):
    rect { pos.x, pos.y, TILE_SIZE, TILE_SIZE },
    neighbour { nullptr, nullptr, nullptr, nullptr },
    sprite { sprite_ },
    rock { nullptr } {

}

void Tile::SetNeighbour(Direction dir, Tile* tile) {
    int index = static_cast<int>(dir);

    if (neighbour[index] != nullptr) {
        Point oldPos = neighbour[index]->GetPos();
        Point newPos = tile->GetPos();
        if (oldPos.x != newPos.x || oldPos.y != newPos.y) {
            WARN(StringFormat("Neighbour of tile is overwritten: tile: %d/%d, old nb: %d/%d, new nb: %d/%d",
                GetPos().x,
                GetPos().y,
                oldPos.x,
                oldPos.y,
                newPos.x,
                newPos.y));
        }
    }
    neighbour[index] = tile;
}

Tile* Tile::GetNeighbour(Direction dir) const {
    return neighbour[static_cast<int>(dir)];
}

Point Tile::GetPos() const {
    return Point{ rect.x, rect.y };
}

void Tile::Draw(const Point& camera, const Point& offset) {
    if (HasRock())
        rock->GetSprite().Draw(Point{ offset.x + rect.x - camera.x, offset.y + rect.y - camera.y });
    else
        sprite.Draw(Point{ offset.x + rect.x - camera.x, offset.y + rect.y - camera.y });
}

void Tile::AddRock(std::unique_ptr<Rock> rock_) {
    if (rock != nullptr) {
        WARN(StringFormat("Overwriting rock occurence on tile (%d/%d)", rect.x, rect.y));
    }
    rock = std::move(rock_);
}

bool Tile::HasRock() const {
    return rock != nullptr;
}

bool Tile::IsTraversable() const {
    return !HasRock();
}

void Tile::MarkRed() {
    sprite.MarkRed();
}

void LinkRows(Tile* topRow, Tile* botRow) {
    if (topRow == nullptr || botRow == nullptr)
        return;

    DEBUG(StringFormat("Linking rows: 0x%X (%d/%d) with 0x%X (%d/%d)",
        topRow,
        topRow->GetPos().x,
        topRow->GetPos().y,
        botRow,
        botRow->GetPos().x,
        botRow->GetPos().y));

    while (topRow != nullptr && botRow != nullptr) {
        topRow->SetNeighbour(Direction::SOUTH, botRow);
        botRow->SetNeighbour(Direction::NORTH, topRow);
        topRow = topRow->GetNeighbour(Direction::EAST);
        botRow = botRow->GetNeighbour(Direction::EAST);

    }
    if (topRow != botRow) {
        WARN(StringFormat("Top and bottom row not both NULL after linking: top: 0x%X, bot: 0x%X",
            topRow,
            botRow));
    }
}

}
