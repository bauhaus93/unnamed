#include "SDLException.h"

SDLException::SDLException(const std::string& function):
    GameException { "SDLException", function, SDL_GetError() } {
}
