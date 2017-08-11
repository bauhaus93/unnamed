#pragma once

#include <SDL2/SDL.h>

#include "exception/GameException.h"

namespace unnamed::sdl {

class SDLException: public exception::GameException {

public:
    explicit				SDLException(const std::string& function);


};

}
