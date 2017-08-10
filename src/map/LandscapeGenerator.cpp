#include "LandscapeGenerator.h"


LandscapeGenerator::LandscapeGenerator(SDLWrapper& sdlWrapper_, Atlas& atlas_, unsigned int seed):
    sdlWrapper { sdlWrapper_ },
    atlas { atlas_ },
    rng { seed },
    floorVariationNoise { rng.Random() },
    terrainTypeNoise { rng.Random() } {
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
    AtlasElement& element = CreateFloorSprite(tileRect);
    Tile* tile = new Tile(Point{ tileRect.x, tileRect.y }, element);

    if (HasRock(tileRect)) {
        std::unique_ptr<Rock> rock = std::make_unique<Rock>(CreateRockSprite(tileRect));
        tile->AddRock(std::move(rock));
    }

    return tile;
}

AtlasElement& LandscapeGenerator::CreateFloorSprite(const Rect& rect) {
    AtlasElement& element = atlas.AddElement(Size{ rect.w, rect.h });

    atlas.SetAsRenderTarget();

    sdlWrapper.DrawFillRect(element.GetRect(), Color{  0xA0, 0xA0, 0xA0, 0xFF });
    Rect spriteRect = element.GetRect();
    for (int y = 0; y < rect.h; y++) {
        for (int x = 0; x < rect.w; x++) {
            double noise = floorVariationNoise.GetOctavedNoise(rect.x + x, rect.y + y, 6, 0.3, 0.005);
            noise = (1.0 + noise) / 2.0;
            uint8_t col = 0xA0;

            if (noise < 0.1)
                col *= 0.8;
            else if (noise < 0.15)
                col *= 0.85;
            else if (noise < 0.25)
                col *= 0.9;
            else if (noise < 0.3)
                col *= 0.95;
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



AtlasElement& LandscapeGenerator::CreateRockSprite(const Rect& rect) {
    AtlasElement& element = atlas.AddElement(Size{ rect.w, rect.h });
    Rect spriteRect = element.GetRect();

    atlas.SetAsRenderTarget();
    sdlWrapper.DrawFillRect(spriteRect, Color{ 0xA0, 0xA0, 0xA0, 0xFF });
    sdlWrapper.DrawRoundedFillRect(spriteRect, 15, Color{ 0x50, 0x50, 0x50, 0xFF });

    /*for (int y = 0; y < rect.h; y++) {
        for (int x = 0; x < rect.w; x++) {
            double noise = floorVariationNoise.GetOctavedNoise(rect.x + x, rect.y + y, 10, 1.4, 0.00005);
            noise = (1.0 + noise) / 2.0;
            uint8_t col = 0x30;
            if (noise < 0.1)
                col *= 0.75;
            else if (noise < 0.2)
                col *= 0.80;
            else if (noise < 0.3)
                col *= 0.85;
            else if (noise < 0.4)
                col *= 0.9;
            if (noise < 0.4) {
                sdlWrapper.SetDrawColor(Color{  col,
                                            col,
                                            col,
                                            0xFF });
                                            sdlWrapper.DrawPoint(Point{ spriteRect.x + x, spriteRect.y + y });
            }
        }
    }
    sdlWrapper.SetDrawColor(Color{  0xFF,
                                    0xFF,
                                    0xFF,
                                    0xFF });*/
    //sdlWrapper.DrawRect(spriteRect, Color{ 0xFF, 0xFF, 0xFF, 0xFF });
    sdlWrapper.ClearRenderTarget();
    return element;
}

bool LandscapeGenerator::HasRock(const Rect& tileRect) {
    return (1 + terrainTypeNoise.GetOctavedNoise(tileRect.x / tileRect.w, tileRect.y / tileRect.h, 2, 5.0, 0.025)) / 2 < 0.33;
}

uint8_t LandscapeGenerator::GetNeighbourRockMask(const Rect& tileRect) {
    uint8_t mask = 0;

    if (HasRock(Rect{ tileRect.x, tileRect.y - 1, tileRect.w, tileRect.h })) {
        mask |= 1;
    }
    if (HasRock(Rect{ tileRect.x + 1, tileRect.y, tileRect.w, tileRect.h })) {
        mask |= 2;
    }
    if (HasRock(Rect{ tileRect.x, tileRect.y + 1, tileRect.w, tileRect.h })) {
        mask |= 4;
    }
    if (HasRock(Rect{ tileRect.x - 1, tileRect.y, tileRect.w, tileRect.h })) {
        mask |= 8;
    }
    return mask;
}
