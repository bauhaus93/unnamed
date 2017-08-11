#include "EventKeyDown.h"

namespace unnamed::event {

EventKeyDown::EventKeyDown(Key key_):
    Event(EventType::KEY_DOWN),
    key { key_ } {
}

Key EventKeyDown::GetKey() const {
    return key;
}

}
