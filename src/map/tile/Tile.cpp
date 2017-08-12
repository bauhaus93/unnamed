#include "Tile.h"

namespace unnamed::map {

Tile::Tile(const Point& pos, std::shared_ptr<atlas::Element>& sprite_):
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
    switch(dir) {
    case Direction::NORTH: return neighbour[0];
    case Direction::EAST:  return neighbour[1];
    case Direction::SOUTH: return neighbour[2];
    case Direction::WEST:  return neighbour[3];
    case Direction::NORTH_EAST:
        if (neighbour[0] != nullptr)
            return neighbour[0]->GetNeighbour(Direction::EAST);
        else if (neighbour[1] != nullptr)
            return neighbour[1]->GetNeighbour(Direction::NORTH);
        return nullptr;
    case Direction::SOUTH_EAST:
        if (neighbour[2] != nullptr)
            return neighbour[2]->GetNeighbour(Direction::EAST);
        else if (neighbour[1] != nullptr)
            return neighbour[1]->GetNeighbour(Direction::SOUTH);
        return nullptr;
    case Direction::SOUTH_WEST:
        if (neighbour[2] != nullptr)
            return neighbour[2]->GetNeighbour(Direction::WEST);
        else if (neighbour[3] != nullptr)
            return neighbour[3]->GetNeighbour(Direction::SOUTH);
        return nullptr;
    case Direction::NORTH_WEST:
        if (neighbour[0] != nullptr)
            return neighbour[0]->GetNeighbour(Direction::WEST);
        else if (neighbour[3] != nullptr)
            return neighbour[3]->GetNeighbour(Direction::NORTH);
        return nullptr;
    default:
        ERROR("Unknown Direction case in Tile::GetNeighbour");
        return nullptr;
    }
}

Tile* Tile::GetNeighbourByPoint(const Point& p) const {
    for (int i = 0; i < 8; i++) {
        Tile* currNB = GetNeighbour(static_cast<Direction>(i));
        if (currNB != nullptr) {
            if (PointInRectangle(p, currNB->GetRect())) {
                return currNB;
            }
        }
    }
    return nullptr;
}

Point Tile::GetPos() const {
    return Point{ rect.x, rect.y };
}

Rect Tile::GetRect() const {
    return rect;
}

void Tile::Draw(const Point& camera, const Point& offset) {
    if (HasRock())
        rock->GetSprite()->Draw(Point{ offset.x + rect.x - camera.x, offset.y + rect.y - camera.y });
    else
        sprite->Draw(Point{ offset.x + rect.x - camera.x, offset.y + rect.y - camera.y });
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
    sprite->MarkRed();
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
