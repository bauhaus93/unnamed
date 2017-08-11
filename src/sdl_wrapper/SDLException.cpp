#include "SDLException.h"

namespace unnamed::sdl {

SDLException::SDLException(const std::string& function):
    GameException { "SDLException", function, SDL_GetError() } {
}

}
