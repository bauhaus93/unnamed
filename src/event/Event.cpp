#include "Event.h"

Event::Event():
    type { EventType::NONE } {
}

Event::Event(EventType type_):
    type { type_ } {
}

Event::Event(const Event& other):
    type { other.type } {

}

EventType Event::GetType() const {
    return type;
}

void Event::SetType(EventType type_) {
    type = type_;
}
