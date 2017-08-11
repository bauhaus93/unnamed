#include "LandscapeGenerator.h"

namespace unnamed::map {

int distance(const Point& a, const Point& b);

LandscapeGenerator::LandscapeGenerator(sdl::Wrapper& sdlWrapper_, atlas::Atlas& atlas_, unsigned int seed):
    sdlWrapper { sdlWrapper_ },
    atlas { atlas_ },
    rng { seed },
    floorVariationNoise { rng.Random() },
    rockNoise { rng.Random() } {
}

Tile* LandscapeGenerator::Generate(const Rect& fieldRect) {
    INFO(StringFormat("Creating landscape %dx%d", fieldRect.w, fieldRect.h));

    Tile* root = nullptr;
    Tile* prevRow = nullptr;
    Rect currRect{ fieldRect.x, fieldRect.y, TILE_SIZE, TILE_SIZE };
    for(int y = 0; y < fieldRect.h; y++) {
        Tile* currRow = CreateTile(currRect);
        if (root == nullptr)
            root = currRow;
        Tile* currTile = currRow;
        for(int x = 0; x + 1 < fieldRect.w; x++) {
            currRect.x += TILE_SIZE;    //bc 1st tile created in outer loop
            Tile* nextTile = CreateTile(currRect);
            currTile->SetNeighbour(Direction::EAST, nextTile);
            nextTile->SetNeighbour(Direction::WEST, currTile);
            if (prevRow != nullptr) {
                currTile->SetNeighbour(Direction::NORTH, prevRow);
                prevRow->SetNeighbour(Direction::SOUTH, currTile);
                prevRow = prevRow->GetNeighbour(Direction::EAST);
            }
            currTile = nextTile;
        }

        if (prevRow != nullptr) {
            currTile->SetNeighbour(Direction::NORTH, prevRow);
            prevRow->SetNeighbour(Direction::SOUTH, currTile);
            prevRow = prevRow->GetNeighbour(Direction::EAST);
        }

        prevRow = currRow;
        currRect.x = fieldRect.x;
        currRect.y += TILE_SIZE;
    }
    return root;
}

Tile* LandscapeGenerator::CreateTile(const Rect& tileRect) {
    std::shared_ptr<atlas::Element> element = CreateFloorSprite(tileRect);
    Tile* tile = new Tile(Point{ tileRect.x, tileRect.y }, element);
    uint8_t rockMask = GetNeighbourRockMask(tileRect);

    if (HasRock(tileRect)) {
        std::unique_ptr<Rock> rock = std::make_unique<Rock>(CreateRockSprite(tileRect, rockMask));
        tile->AddRock(std::move(rock));
    }

    return tile;
}

std::shared_ptr<atlas::Element> LandscapeGenerator::CreateFloorSprite(const Rect& rect) {
    std::shared_ptr<atlas::Element> element = atlas.AddElement(Size{ rect.w, rect.h });

    atlas.SetAsRenderTarget();
    Rect spriteRect = element->GetRect();
    sdlWrapper.DrawFillRect(spriteRect, Color{  0xA0, 0xA0, 0xA0, 0xFF });

    for (int y = 0; y < rect.h; y++) {
        for (int x = 0; x < rect.w; x++) {
            double noise = floorVariationNoise.GetOctavedNoise(rect.x + x, rect.y + y, 6, 0.3, 0.005);
            noise = (1.0 + noise) / 2.0;
            uint8_t col = 0xA0;

            if (noise < 0.1)
                col = static_cast<uint8_t>(col * 0.8);
            else if (noise < 0.15)
				col = static_cast<uint8_t>(col * 0.85);
            else if (noise < 0.25)
				col = static_cast<uint8_t>(col * 0.9);
            else if (noise < 0.3)
				col = static_cast<uint8_t>(col * 0.95);
            if (noise < 0.3) {
                sdlWrapper.SetDrawColor(Color{  col,
                                                col,
                                                col,
                                                0xFF });

                sdlWrapper.DrawPoint(   Point{ spriteRect.x + x, spriteRect.y + y },
                                        Color{  col, col, col, col });
            }
        }
    }
    //sdlWrapper.DrawRect(spriteRect, Color{  0xFF, 0xFF, 0xFF, 0xFF });
    sdlWrapper.ClearRenderTarget();
    return element;
}


std::shared_ptr<atlas::Element> LandscapeGenerator::CreateRockSprite(const Rect& rect, uint8_t rockMask) {
    std::shared_ptr<atlas::Element> element = atlas.AddElement(Size{ rect.w, rect.h });
    Rect spriteRect = element->GetRect();
    const int CORNER_RADIUS = 14;

    atlas.SetAsRenderTarget();

    if (rockMask == (1 | 2 | 4 | 8)) {
        sdlWrapper.DrawFillRect(spriteRect, Color{ 0x50, 0x50, 0x50, 0xFF });
    }
    else {
        sdlWrapper.DrawFillRect(spriteRect, Color{ 0xA0, 0xA0, 0xA0, 0xFF });
        sdlWrapper.DrawRoundedFillRect(spriteRect, CORNER_RADIUS, Color{ 0x50, 0x50, 0x50, 0xFF });
        if ((rockMask & (1 | 2))) {
            Rect r { spriteRect.x + spriteRect.w - CORNER_RADIUS,
                     spriteRect.y,
                     CORNER_RADIUS,
                     CORNER_RADIUS };
            sdlWrapper.DrawFillRect(r, Color{ 0x50, 0x50, 0x50, 0xFF });
        }
        if ((rockMask & (2 | 4))) {
            Rect r { spriteRect.x + spriteRect.w - CORNER_RADIUS,
                     spriteRect.y + spriteRect.h - CORNER_RADIUS,
                     CORNER_RADIUS,
                     CORNER_RADIUS };
            sdlWrapper.DrawFillRect(r, Color{ 0x50, 0x50, 0x50, 0xFF });
        }
        if ((rockMask & (4 | 8))) {
            Rect r { spriteRect.x,
                     spriteRect.y + spriteRect.h - CORNER_RADIUS,
                     CORNER_RADIUS,
                     CORNER_RADIUS };
            sdlWrapper.DrawFillRect(r, Color{ 0x50, 0x50, 0x50, 0xFF });
        }
        if ((rockMask & (8 | 1))) {
            Rect r { spriteRect.x,
                     spriteRect.y,
                     CORNER_RADIUS,
                     CORNER_RADIUS };
            sdlWrapper.DrawFillRect(r, Color{ 0x50, 0x50, 0x50, 0xFF });
        }
    }
    /*for (int y = 0; y < rect.h; y++) {
        for (int x = 0; x < rect.w; x++) {
            double noise = floorVariationNoise.GetOctavedNoise(rect.x + x, rect.y + y, 4, 1.2, 0.002);
            noise = (1.0 + noise) / 2.0;
            uint8_t col = 0x50;
            if (noise < 0.1)
                col *= 0.75;
            else if (noise < 0.2)
                col *= 0.80;
            else if (noise < 0.3)
                col *= 0.85;
            else if (noise < 0.4)
                col *= 0.9;
            if (noise < 0.4) {
                Point pos { spriteRect.x + x, spriteRect.y + y };

                if (distance(pos, Point{ spriteRect.x + spriteRect.w / 2, spriteRect.y + spriteRect.h / 2 }) <= TILE_SIZE / 2)
                    sdlWrapper.DrawPoint(Point{ spriteRect.x + x, spriteRect.y + y }, Color{ col, col, col, 0xFF });
                else {
                    int distNE = distance(pos, Point{ spriteRect.x + spriteRect.w - CORNER_RADIUS, spriteRect.y + CORNER_RADIUS });
                    int distSE = distance(pos, Point{ spriteRect.x + spriteRect.w - CORNER_RADIUS, spriteRect.y + spriteRect.h - CORNER_RADIUS });
                    int distSW = distance(pos, Point{ spriteRect.x + CORNER_RADIUS, spriteRect.y + spriteRect.h - CORNER_RADIUS });
                    int distNW = distance(pos, Point{ spriteRect.x + CORNER_RADIUS, spriteRect.y + CORNER_RADIUS });

                    if (distNE <= CORNER_RADIUS || ((rockMask & (1 | 2)) && distNE <= 19))
                        sdlWrapper.DrawPoint(Point{ spriteRect.x + x, spriteRect.y + y }, Color{ col, col, col, 0xFF });
                    else if (distSE <= CORNER_RADIUS || ((rockMask & (2 | 4)) && distSE <= 19))
                        sdlWrapper.DrawPoint(Point{ spriteRect.x + x, spriteRect.y + y }, Color{ col, col, col, 0xFF });
                    else if (distSW <= CORNER_RADIUS || ((rockMask & (4 | 8)) && distSW <= 19))
                        sdlWrapper.DrawPoint(Point{ spriteRect.x + x, spriteRect.y + y }, Color{ col, col, col, 0xFF });
                    else if (distNW <= CORNER_RADIUS || ((rockMask & (8 | 1)) && distNW <= 19))
                        sdlWrapper.DrawPoint(Point{ spriteRect.x + x, spriteRect.y + y }, Color{ col, col, col, 0xFF });
                }
            }
        }
    }*/

    //sdlWrapper.DrawRect(spriteRect, Color{ 0xFF, 0xFF, 0xFF, 0xFF });
    sdlWrapper.ClearRenderTarget();
    return element;
}

bool LandscapeGenerator::HasRock(const Rect& tileRect) {
    return (1 + rockNoise.GetOctavedNoise(tileRect.x / tileRect.w, tileRect.y / tileRect.h, 2, 5.0, 0.025)) / 2 < 0.33;
}

uint8_t LandscapeGenerator::GetNeighbourRockMask(const Rect& tileRect) {
    uint8_t mask = 0;

    if (HasRock(Rect{ tileRect.x, tileRect.y - TILE_SIZE, tileRect.w, tileRect.h })) {
        mask |= 1;
    }
    if (HasRock(Rect{ tileRect.x + TILE_SIZE, tileRect.y, tileRect.w, tileRect.h })) {
        mask |= 2;
    }
    if (HasRock(Rect{ tileRect.x, tileRect.y + TILE_SIZE, tileRect.w, tileRect.h })) {
        mask |= 4;
    }
    if (HasRock(Rect{ tileRect.x - TILE_SIZE, tileRect.y, tileRect.w, tileRect.h })) {
        mask |= 8;
    }
    return mask;
}

int distance(const Point& a, const Point& b) {
    int diffX = a.x - b.x;
    int diffY = a.y - b.y;
    diffX *= diffX;
    diffY *= diffY;
    return static_cast<int>(sqrt(diffX + diffY));
}

}
