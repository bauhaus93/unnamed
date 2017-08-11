#pragma once

#include "Event.h"

namespace unnamed::event {

enum class Key {
    UNKNOWN,
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class EventKeyDown: public Event {

    Key         key;

public:
    explicit    EventKeyDown(Key key_);
    Key         GetKey() const;
};

}
