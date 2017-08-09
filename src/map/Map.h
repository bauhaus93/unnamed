#pragma once

#include "atlas/Atlas.h"
#include "sdl_wrapper/SDLWrapper.h"
#include "logger/StdLogger.h"
#include "Tile.h"

class Map {

    Size                size;
    Tile*               root;
    Tile*               camera;

public:

                        Map(const Size& size_, Atlas& atlas, SDLWrapper& sdlWrapper);
                        ~Map();
    void                Draw(const Rect& destRect);
    void                MoveCamera(Direction dir);

};
