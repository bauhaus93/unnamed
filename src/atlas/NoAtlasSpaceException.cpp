#include "NoAtlasSpaceException.h"

namespace unnamed::atlas {

NoAtlasSpaceException::NoAtlasSpaceException(const Size<int>& size):
    GameException { "NoAtlasSpaceException",
                    "Atlas::AddElement",
                    StringFormat("No space available for size %dx%d", size.x, size.y) } {

}

}
