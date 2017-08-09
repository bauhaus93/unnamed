#include "NoAtlasSpaceException.h"

NoAtlasSpaceException::NoAtlasSpaceException(const Size& size):
    GameException { "NoAtlasSpaceException",
                    "Atlas::AddElement",
                    StringFormat("No space available for size %dx%d", size.x, size.y) } {

}
