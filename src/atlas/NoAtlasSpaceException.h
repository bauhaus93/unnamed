#pragma once

#include <exception>
#include <string>

#include "exception/GameException.h"
#include "common/Size.h"
#include "common/StringFormat.h"

class NoAtlasSpaceException : public GameException {

public:
    explicit NoAtlasSpaceException(const Size& size);
};
