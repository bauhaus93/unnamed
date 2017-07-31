#pragma once

#ifdef _WIN32
#include <SDL/SDL.h>
#endif
#ifdef __linux__
#include <SDL2/SDL.h>
#endif

#include "logger/StdLogger.h"
#include "SDLException.h"

class SDLWrapper {


public:

                    SDLWrapper();
                    ~SDLWrapper();

};
