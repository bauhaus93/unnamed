#pragma once

#include <exception>
#include <string>

#include "exception/GameException.h"
#include "common/Size.h"
#include "common/StringFormat.h"

namespace unnamed::atlas {

class NoAtlasSpaceException : public exception::GameException {

public:
    explicit NoAtlasSpaceException(const Size& size);
};

}
