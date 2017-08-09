#include "Tile.h"

AtlasElement&   CreateAtlasElement(const Point& pos, Atlas& atlas, SDLWrapper& sdlWrapper);


Tile::Tile(const Point& pos, Atlas& atlas, SDLWrapper& sdlWrapper):
    rect { pos.x, pos.y, TILE_SIZE, TILE_SIZE },
    neighbour { nullptr, nullptr, nullptr, nullptr },
    sprite { CreateAtlasElement(pos, atlas, sdlWrapper) } {

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

void Tile::ExpandRow(int count, Atlas& atlas, SDLWrapper& sdlWrapper) {
    Tile* currTile = this;

    while (count-- > 0) {
        Point currPos = currTile->GetPos();
        Tile* nextTile = new Tile(  Point{  currPos.x + TILE_SIZE,
                                            currPos.y },
                                    atlas,
                                    sdlWrapper);
        currTile->SetNeighbour(Direction::EAST, nextTile);
        nextTile->SetNeighbour(Direction::WEST, currTile);
        currTile = nextTile;
    }
}

void Tile::ExpandColumn(int count, Atlas& atlas, SDLWrapper& sdlWrapper) {
    Tile* currTile = this;

    while (count-- > 0) {
        Point currPos = currTile->GetPos();
        Tile* nextTile = new Tile(  Point{  currPos.x,
                                            currPos.y + TILE_SIZE },
                                    atlas,
                                    sdlWrapper);
        currTile->SetNeighbour(Direction::SOUTH, nextTile);
        nextTile->SetNeighbour(Direction::NORTH, currTile);
        currTile = nextTile;
    }
}

Tile* Tile::GetNeighbour(Direction dir) const {
    return neighbour[static_cast<int>(dir)];
}

Point Tile::GetPos() const {
    return Point{ rect.x, rect.y };
}

void Tile::Draw(const Point& camera, const Point& offset) {
    sprite.Draw(Point{ offset.x + rect.x - camera.x, offset.y + rect.y - camera.y });
}


AtlasElement& CreateAtlasElement(const Point& pos, Atlas& atlas, SDLWrapper& sdlWrapper) {

    AtlasElement& element = atlas.AddElement(Size{ TILE_SIZE, TILE_SIZE });

    atlas.SetAsRenderTarget();
    sdlWrapper.SetDrawColor(Color{  static_cast<uint8_t>(pos.x % 256),
                                    static_cast<uint8_t>(pos.y % 256),
                                    static_cast<uint8_t>((pos.x + pos.y) % 256),
                                    0xFF });
    sdlWrapper.DrawFillRect(element.GetRect());
    sdlWrapper.ClearRenderTarget();

    return element;
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
